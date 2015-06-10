#ifndef __CONST_H
#define __CONST_H

#ifdef __ASSEMBLY__
#define _AC(X,Y)	X
#define _AT(T,X)	X
#else
#define __AC(X,Y)	(X##Y)
#define _AC(X,Y)	__AC(X,Y)
#define _AT(T,X)	((T)(X))
#endif
#define __stringify_1(x...) #x
#define __stringify(x...)   __stringify_1(x)
#endif
