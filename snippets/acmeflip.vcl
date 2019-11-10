#
# VCL file for running certbot on an active/passive cluster.
#
# Flips where /.well-known/acme-challenge/ requests are sent.
#
# There is of course a race condition here, if both nodes attempt to renew
# at the same time.
#
# We can in theory fix that by putting the challenge into vmod-var as well, and
# match that with the right node, but we'll leave that for a future improvement.
#
# Usage:
# * Your default.vcl should define two backends: certbot_active and certbot_passive
# * "curl -X POST https://dnsname/.acme-target/active" to point future requests to
#   /.well-known/acme-challenge/ to the active one.
# * "curl -X POST https://dnsname/.acme-target/passive" to point future requests to
#   /.well-known/acme-challenge/ to the passive one.
#
# backend certbot_active          { .host = "activenode.example.com"; .port = "8080"; }
# backend certbot_passive         { .host = "passivenode.example.com"; .port = "8080"; }
#
# certbot must run --standalone and listen to the mentioned port.
#
# Author: Lasse Karstensen <lasse@isokron.no>, August 2019.
#
vcl 4.0;

import std;
import var;


sub vcl_init {
    var.global_set("certbot_target", "active");
}

sub acmeflip_recv {
    if (req.url ~ "^/.well-known/acme-challenge/") {
        if (var.global_get("certbot_target") == "active") {
            set req.backend_hint = certbot_active;
        } elif (var.global_get("certbot_target") == "passive") {
            set req.backend_hint = certbot_passive;
        } else {
            return(synth(500));
        }
        return(pass);
    }

    if (req.url ~ "^/.acme-target/") {
        if (req.method == "POST") {
            if (req.url ~ "^/.acme-target/set_active$") {
                var.global_set("certbot_target", "active");
                std.syslog(9, "acmeflip: certbot_target set to active node by " + client.ip);
            } elif (req.url ~ "^/.acme-target/set_passive$") {
                var.global_set("certbot_target", "passive");
                std.syslog(9, "acmeflip: certbot_target set to passive node by " + client.ip);
            }
        }
        # Implicit support for GET requests.
        return(synth(299, var.global_get("certbot_target")));
    }
}


sub acmeflip_synth {
   if (resp.status == 299) {
        synthetic("Target is " + resp.reason);
        set resp.status = 200;
        set resp.http.Content-Type = "text/plain";
        return(deliver);
    }
}
