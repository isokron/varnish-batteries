#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cache/cache.h"

#include "vmod_encoding_if.h"
#include "urlcode.h"
#include "base64.h"

int v_matchproto_(vmod_event_f)
event_function(VRT_CTX, struct vmod_priv *priv, enum vcl_event_e e)
{
	return(0);
}

// #if VRT_MAJOR_VERSION == 7
#if 1
#define WS_RES(c) WS_Reserve(c, 0)
#else
#define WS_RES(c) WS_ReserveAll(c)
#endif

VCL_STRING
vmod_urlencode(VRT_CTX, VCL_STRING s)
{
	if (s == NULL) {
		return(NULL);
	}
	int destlen = WS_RES(ctx->ws);
	AN(destlen);

	int n = urlencode(s, ctx->ws->f, destlen-1);

	if (n < 0) {
		WS_Release(ctx->ws, 0);
		return(NULL);
	}

	char *value = ctx->ws->f;
	WS_Release(ctx->ws, n);
	return(value);
}

VCL_STRING
vmod_urldecode(VRT_CTX, VCL_STRING s)
{
	if (s == NULL) {
		return(NULL);
	}
	int destlen = WS_RES(ctx->ws);
	AN(destlen);

	int n = urldecode(s, ctx->ws->f, destlen-1);

	if (n < 0) {
		WS_Release(ctx->ws, 0);
		return(NULL);
	}

	char *value = ctx->ws->f;
	WS_Release(ctx->ws, n);
	return(value);
}

VCL_STRING
vmod_b64encode(VRT_CTX, VCL_STRING s)
{
	if (s == NULL) {
		return(NULL);
	}
	int destlen = WS_RES(ctx->ws);
	AN(destlen);

	int n = pg_b64_encode(s, strlen(s), ctx->ws->f, destlen-1);
	if (n < 0) {
		WS_Release(ctx->ws, 0);
		return(NULL);
	}

	char *value = ctx->ws->f;
	WS_Release(ctx->ws, n+1);
	return(value);
}

VCL_STRING
vmod_b64decode(VRT_CTX, VCL_STRING s)
{
	if (s == NULL) {
		return(NULL);
	}
	int destlen = WS_RES(ctx->ws);
	AN(destlen);

	int n = pg_b64_decode(s, strlen(s), ctx->ws->f, destlen-1);
	if (n < 0) {
		WS_Release(ctx->ws, 0);
		return(NULL);
	}

	char *value = ctx->ws->f;
	WS_Release(ctx->ws, n+1);
	return(value);
}
