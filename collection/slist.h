/*
 * Collections-C
 * Copyright (C) 2013-2015 Srđan Panić <srdja.panic@gmail.com>
 *
 * This file is part of Collections-C.
 *
 * Collections-C is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Collections-C is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Collections-C.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SLIST_H_
#define SLIST_H_

#include "common.h"

/**
 * A singly linked list. List is a sequential structure that supports constant time
 * insertion, deletion  and lookup at the beginning of the list, while the worst
 * case for these operations is linear time.
 */
typedef struct slist_s SList;

/**
 * SList node.
 *
 * @note Modifying the links may invalidate the list structure.
 */
typedef struct snode_s {
    void           *data;
    struct snode_s *next;
} SNode;

/**
 * SList iterator object. Used to iterate over the elements of the list
 * in an ascending order. The iterator also supports operations for safely
 * adding and removing elements during iteration.
 *
 * @code
 * SListIter i;
 * slist_iter_init(&i);
 *
 * while (slist_iter_has_next(&i)) {
 *     MyType *e = slist_iter_next(&i);
 * }
 * @endcode
 */
typedef struct slist_iter_s {
    size_t  index;
    SList  *list;
    SNode   *next;
    SNode   *current;
    SNode   *prev;
} SListIter;

/**
 * SList configuration object. Used to initalize a new SList with specific
 * values.
 *
 * @code
 * SListConf c;
 * slist_conf_init(&c);
 *
 * c.mem_alloc  = mymalloc;
 * c.mem_free   = myfree;
 * c.mem_calloc = mycalloc;
 *
 * SList *l = slist_new_conf(&c);
 * @endcode
 */
typedef struct slist_conf_s {
    void  *(*mem_alloc)  (size_t size);
    void  *(*mem_calloc) (size_t blocks, size_t size);
    void   (*mem_free)   (void *block);
} SListConf;

void          slist_conf_init       (SListConf *conf);
enum cc_stat  slist_new             (SList **list);
enum cc_stat  slist_new_conf        (SListConf const * const conf, SList **list);
bool          slist_destroy         (SList *list);
bool          slist_destroy_free    (SList *list);

enum cc_stat  slist_splice          (SList *list1, SList *list2);
enum cc_stat  slist_splice_at       (SList *list1, SList *list2, size_t index);

enum cc_stat  slist_add             (SList *list, void *element);
enum cc_stat  slist_add_at          (SList *list, void *element, size_t index);
enum cc_stat  slist_add_all         (SList *list1, SList *list2);
enum cc_stat  slist_add_all_at      (SList *list1, SList *list2, size_t index);
enum cc_stat  slist_add_first       (SList *list, void *element);
enum cc_stat  slist_add_last        (SList *list, void *element);

enum cc_stat  slist_remove          (SList *list, void *element, void **out);
enum cc_stat  slist_remove_first    (SList *list, void **out);
enum cc_stat  slist_remove_last     (SList *list, void **out);
enum cc_stat  slist_remove_at       (SList *list, size_t index, void **out);

enum cc_stat  slist_remove_all      (SList *list);
enum cc_stat  slist_remove_all_free (SList *list);

enum cc_stat  slist_get_at          (SList *list, size_t index, void **out);
enum cc_stat  slist_get_first       (SList *list, void **out);
enum cc_stat  slist_get_last        (SList *list, void **out);

enum cc_stat  slist_sublist         (SList *list, size_t from, size_t to, SList **out);
enum cc_stat  slist_copy_shallow    (SList *list, SList **out);
enum cc_stat  slist_copy_deep       (SList *list, void *(*cp) (void*), SList **out);

enum cc_stat  slist_replace_at      (SList *list, void *element, size_t index, void **out);

size_t        slist_contains        (SList *list, void *element);
enum cc_stat  slist_index_of        (SList *list, void *element, size_t *index);
enum cc_stat  slist_to_array        (SList *list, void ***out);

void          slist_reverse         (SList *list);
enum cc_stat  slist_sort            (SList *list, int (*cmp) (void const*, void const*));
size_t        slist_size            (SList *list);

void          slist_foreach         (SList *list, void (*op) (void *));

void          slist_iter_init       (SListIter *iter, SList *list);
enum cc_stat  slist_iter_remove     (SListIter *iter, void **out);
enum cc_stat  slist_iter_add        (SListIter *iter, void *element);
enum cc_stat  slist_iter_replace    (SListIter *iter, void *element, void **out);
enum cc_stat  slist_iter_next       (SListIter *iter, void **out);
size_t        slist_iter_index      (SListIter *iter);

#endif /* SLIST_H_ */
