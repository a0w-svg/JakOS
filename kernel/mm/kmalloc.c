#include "./include/kmalloc.h"
#include <stdbool.h>
#include "../../libc/include/string.h"
#include "../../libc/include/mem.h"
#define WORD_SIZE sizeof(void *)
#define ALIGN 8
#define DWORD_SIZE (2 * WORD_SIZE)
#define CHUNK_SIZE (1 << 12)

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define PACK(size, alloc) ((size) | (alloc))
#define GET(p) (*(uintptr_t *)(p))
#define PUT(p, value) (*(uintptr_t *)(p) = (value))
#define GET_SIZE(p) (GET(p) & ~(ALIGN - 1))
#define GET_ALLOC(p) (GET(p) & 0x1)
#define HDRP(bp) ((char *)(bp) - WORD_SIZE)
#define FTRP(bp) ((char *)(bp) + GET_SIZE(HDRP(bp)) - DWORD_SIZE)
#define NEXT_BLKP(bp) ((char *)(bp) + GET_SIZE(((char *)(bp)- WORD_SIZE)))
#define PREV_BLKP(bp) ((char *)(bp) - GET_SIZE(((char *)(bp) - DWORD_SIZE)))
#define MIN_CLASS 5
#define MIN_SIZE (1 << MIN_CLASS)
#define MAX_CLASS 20
#define MAX_SIZE (1 << MAX_CLASS)
#define GET_BIN(c) (uint32_t - __builtin_clz(c))

static char *heap_list_phys;
static void *coalesce(void *bp);
static void *find_fit(size_t a_size);
static void place(void *bp, size_t a_size);

int heap_init(void)
{
    heap_list_phys = heap;
    PUT(heap_list_phys, 0);
    PUT(heap_list_phys + (1 * WORD_SIZE), PACK(ALIGN, 1));
    PUT(heap_list_phys + (2 * WORD_SIZE), PACK(ALIGN, 1));
    char *fblock = heap_list_phys + 2 * WORD_SIZE;
    size_t block_size = ALIGN * ((HEAP_SIZE - 3 * WORD_SIZE) / ALIGN);
    PUT(HDRP(fblock), block_size);
    PUT(FTRP(fblock), block_size);
    PUT(HDRP(NEXT_BLKP(fblock)), PACK(0, 1));
    heap_list_phys += (2 * WORD_SIZE);
    return 0;
}

void *kmalloc(size_t size)
{
    size_t a_size;
    void *bp;

    if(size == 0)
    {
        return NULL;
    }
    if(size <= ALIGN)
    {
        a_size = DWORD_SIZE + ALIGN;
    }
    else
    {
        a_size = ALIGN * ((size + DWORD_SIZE + (ALIGN - 1)) / ALIGN); 
    }

    if((bp = find_fit(a_size)) != NULL)
    {
        place(bp, a_size);
        return bp;
    } 
    return NULL;
}
void free(void *bp)
{
    size_t size;
    if(bp == NULL)
    {
        return;
    }
    size = GET_SIZE(HDRP(bp));
    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK(size, 0));
    coalesce(bp);
}
void *realkalloc(void *pointer, size_t size)
{
    size_t old_size;
    void *new_pointer;
    if(size == 0)
    {
        free(pointer);
        return NULL;
    }
    if(pointer == NULL)
    {
        return (kmalloc(size));
    }
    new_pointer = kmalloc(size);
    if(new_pointer == NULL)
    {
        return NULL;
    }
    old_size = GET_SIZE(HDRP(pointer));
    if(size < old_size)
    {
        old_size = size;
    }
    memcpy(new_pointer, pointer,old_size);
    free(pointer);
    return new_pointer;
}

static void *coalesce(void *bp)
{
    size_t size = GET_SIZE(HDRP(bp));
    bool prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
    bool next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));

    if(prev_alloc && next_alloc)
    {
        return bp;
    }
    else if(prev_alloc && !next_alloc)
    {
        size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
        PUT(HDRP(bp), PACK(size, 0));
        PUT(FTRP(bp), PACK(size, 0));
    }
    else if(!prev_alloc && next_alloc)
    {
        size += GET_SIZE(HDRP(PREV_BLKP(bp)));
        PUT(FTRP(bp), PACK(size, 0));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        bp = PREV_BLKP(bp);
    }
    else
    {
        size += GET_SIZE(HDRP(PREV_BLKP(bp))) +
                GET_SIZE(FTRP(NEXT_BLKP(bp)));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
        bp = PREV_BLKP(bp);
    }
    return bp;
}

static void *find_fit(size_t a_size)
{
    void *bp;
    for(bp = heap_list_phys; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp))
    {
        if(!GET_ALLOC(HDRP(bp)) && a_size <= GET_SIZE(HDRP(bp)))
        {
            return bp;
        }
    }
    return NULL;
}
static void place(void *bp, size_t a_size)
{
    size_t c_size  = GET_SIZE(HDRP(bp));
    if((c_size - a_size) >= (DWORD_SIZE))
    {
        PUT(HDRP(bp), PACK(a_size, 1));
        PUT(FTRP(bp), PACK(a_size, 1));
        bp = NEXT_BLKP(bp);
        PUT(HDRP(bp), PACK(c_size - a_size, 0));
        PUT(FTRP(bp), PACK(c_size - a_size, 0));
    }
    else
    {
        PUT(HDRP(bp), PACK(c_size, 1));
        PUT(FTRP(bp), PACK(c_size, 1));
    }
    
}