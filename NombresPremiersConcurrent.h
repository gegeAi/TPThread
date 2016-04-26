#ifndef NOMBRES_PREMIERS_CONCURRENT_H
#define NOMBRES_PREMIERS_CONCURRENT_H

typedef struct Liste Liste;
struct Liste
{
	uint64_t n;
	Liste * suivant;
};

#endif
