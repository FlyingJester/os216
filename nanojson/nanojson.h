/* Copyright (c) 2018 Martin McDonough.  All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef NANOJSON_H
#define NANOJSON_H
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************/

#define NJ_OBJECT_TYPE 1
#define NJ_ARRAY_TYPE 2

/*****************************************************************************/

enum NJ_ElementType {
    NJ_ErrorType,
    NJ_ObjectType,
    NJ_ArrayType,
    NJ_NumberType,
    NJ_StringType,
    NJ_NullType,
    NJ_TrueType,
    NJ_FalseType
};

/*****************************************************************************/
/* API to parse an entire JSON object */

struct NJ_Value;

/*****************************************************************************/

struct NJ_String {
    unsigned len;
    const char *string;
};

/*****************************************************************************/

struct NJ_Array {
    unsigned len;
    struct NJ_Value *values;
};

/*****************************************************************************/

struct NJ_Object {
    unsigned len;
    struct NJ_Value *values;
    struct NJ_String *names;
};

/*****************************************************************************/

struct NJ_Value {
    enum NJ_ElementType type;
    union {
        struct NJ_String string;
        struct NJ_Array array;
        struct NJ_Object object;
        float number;
        struct {
            const char *error; /* Must be freed by the caller. */
            unsigned line, column;
        } error;
    } value;
};

/*****************************************************************************/

void NJ_FreeValue(struct NJ_Value *value);

/*****************************************************************************/

unsigned NJ_ParseRoot(const char *string,
    unsigned len,
    struct NJ_Value *out_value);

/*****************************************************************************/

unsigned NJ_ParseValue(const char *string,
    unsigned len,
    unsigned *i,
    struct NJ_Value *out_value);

/*****************************************************************************/

unsigned NJ_ParseObject(const char *string,
    unsigned len,
    unsigned *i,
    struct NJ_Value *out_value);

/*****************************************************************************/

unsigned NJ_ParseArray(const char *string,
    unsigned len,
    unsigned *i,
    struct NJ_Value *out_value);

/*****************************************************************************/

float NJ_ParseNumber(const char *string, unsigned len, unsigned *i);

/*****************************************************************************/

void NJ_ParseString(const char *string, unsigned len, unsigned *i);

/*****************************************************************************/
/* SAX-style parser. */

struct NJ_TreeElement {
    unsigned short type; /* Either NJ_OBJECT_TYPE or NJ_ARRAY_TYPE */
    union {
        const char *object_element_name;
        unsigned array_element_index;
    };
};

/*****************************************************************************/
/* This callback will be run until it returns 0 on a node.
 * elements is the "path" of this node. It is in build-order.
 * The type of value will never be an array or an object.
 *
 * As an example:
 * {
 *    "element_a":[
 *        true
 *    ]
 * }
 * 
 * The callback will be called with elements:
 *    [{NJ_OBJECT_TYPE, {"element_a"}}, {NJ_ARRAY_TYPE, {0}}]
 * The value will be of type NJ_FalseType
 */
typedef unsigned (*NJ_Callback)(const struct NJ_TreeElement *elements,
    unsigned num_elements,
    const struct NJ_Value *value);

/*****************************************************************************/

void NJ_Parse(NJ_Callback callback, const char *string, unsigned len);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* NANOJSON_H */
