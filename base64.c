#include "base64.h"

static const char b64[] =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static char find_pos(char ch) {
	char *ptr = (char*) strrchr(b64, ch);
	return (ptr - b64);
}

unsigned char *base64_encode(const unsigned char *in, int in_size)
{
	int bit_remain = in_size;
	unsigned char *ret, *dst;
	unsigned bs = 0;
	int shift = 0;
	int out_size = 0;
	int temp = 0;
	temp = (in_size) % 3;
	if (temp > 0) {
		out_size = (in_size/3 + 1) * 4 + 1;
	} else {
		out_size = in_size/3 * 4 + 1;
	}
	ret = dst = (unsigned char *)malloc(out_size);
	if (ret == NULL) return NULL;
	while (bit_remain) {
		bs = (bs << 8) + *in++;
		bit_remain--;
		shift += 2;

		*dst++ = b64[(bs >> shift) & 0x3f];
		if (shift == 6) {
			*dst++ = b64[bs & 0x3f];
			shift = 0;
		}
		if (bit_remain == 0 && shift > 0) {
			*dst++ = b64[(bs << (6-shift)) & 0x3f];
		}

	}
	while ((dst - ret) & 3)
		*dst++ = '=';
	*dst = '\0';
	return ret;
}

unsigned char *base64_decode(const unsigned char *in)
{
	unsigned char *ret, *dst;
	int i, temp = 0;
	unsigned bs = 0;
	unsigned char tmp;
	int in_len = strlen((char *)in);
	int out_len = in_len/4 * 3;
	if (*(in + in_len - 1) == '=') {
		out_len--;
	}
	if (*(in + in_len - 2) == '=') {
		out_len--;
	}
	ret = dst = (unsigned char *)malloc(out_len + 1);
	if (ret == NULL) return NULL;
	while (in_len) {
		tmp = *in++;
		if (tmp == '=') {
			tmp = 0;
		} else {
			tmp = find_pos(tmp);
		}
		bs = (bs << 6) + tmp;
		temp++;
		in_len--;
		if (temp == 4) {
			for (i = 3; i > 0; i--) {
				*dst++ = (unsigned char)((bs >> (i - 1)*8) & 0xff);
			}
			temp = 0;
			bs = 0;
		}
	}
	*dst = '\0';
	return ret;
}
