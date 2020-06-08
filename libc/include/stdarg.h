#ifndef STDARG_H
#define STDARG_H
//variable arguments
typedef __builtin_va_list va_list;

#define va_start(ap, param) __buildin_va_start((ap), (param))
#define va_arg(ap, type)   __buildin_va_arg((ap), (type))
#define va_end(ap)      __buildin_va_end((ap))
#define va_copy(dest, src)  __buildin_va_copy((dest), (src))
#endif