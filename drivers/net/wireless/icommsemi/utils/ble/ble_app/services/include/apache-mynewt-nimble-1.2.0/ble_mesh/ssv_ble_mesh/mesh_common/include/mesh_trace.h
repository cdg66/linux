/*
 * Copyright (c) 2017 Nordic Semiconductor ASA
 * Copyright (c) 2015-2016 Intel Corporation
 * Additional Copyright (c) 2018 Espressif Systems (Shanghai) PTE LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _BLE_MESH_TRACE_H_
#define _BLE_MESH_TRACE_H_

#include "ssv_log.h"
#include "sdkconfig.h"

/* Define common tracing for all */
#ifndef LOG_LEVEL_ERROR
#define LOG_LEVEL_ERROR     1
#endif /* LOG_LEVEL_ERROR */

#ifndef LOG_LEVEL_WARN
#define LOG_LEVEL_WARN      2
#endif /* LOG_LEVEL_WARN */

#ifndef LOG_LEVEL_INFO
#define LOG_LEVEL_INFO      3
#endif /* LOG_LEVEL_INFO */

#ifndef LOG_LEVEL_DEBUG
#define LOG_LEVEL_DEBUG     4
#endif /* LOG_LEVEL_DEBUG */

#ifndef LOG_LEVEL_VERBOSE
#define LOG_LEVEL_VERBOSE   5
#endif /*LOG_LEVEL_VERBOSE */

#ifdef CONFIG_BLE_MESH_STACK_TRACE_LEVEL
#define MESH_LOG_LEVEL      CONFIG_BLE_MESH_STACK_TRACE_LEVEL
#else
#define MESH_LOG_LEVEL      LOG_LEVEL_WARN
#endif

#ifdef CONFIG_BLE_MESH_NET_BUF_TRACE_LEVEL
#define NET_BUF_LOG_LEVEL   CONFIG_BLE_MESH_NET_BUF_TRACE_LEVEL
#else
#define NET_BUF_LOG_LEVEL   LOG_LEVEL_WARN
#endif

#if MESH_BLE_EN
#define MESH_TRACE_TAG      "BLE_MESH"
#else
#define MESH_TRACE_TAG      "BLE"
#endif

#define LOG_ERROR(format, ... )             {if (LOG_LOCAL_LEVEL >= SSV_LOG_ERROR)    ssv_log_write(SSV_LOG_ERROR,   "BT_LOG", MESHLOG_FORMAT(E, format), ssv_log_timestamp(), "BT_LOG", ##__VA_ARGS__); }
#define LOG_WARN(format, ... )              {if (LOG_LOCAL_LEVEL >= SSV_LOG_WARN)     ssv_log_write(SSV_LOG_WARN,    "BT_LOG", MESHLOG_FORMAT(W, format), ssv_log_timestamp(), "BT_LOG", ##__VA_ARGS__); }
#define LOG_INFO(format, ... )              {if (LOG_LOCAL_LEVEL >= SSV_LOG_INFO)     ssv_log_write(SSV_LOG_INFO,    "BT_LOG", MESHLOG_FORMAT(I, format), ssv_log_timestamp(), "BT_LOG", ##__VA_ARGS__); }
#define LOG_DEBUG(format, ... )             {if (LOG_LOCAL_LEVEL >= SSV_LOG_DEBUG)    ssv_log_write(SSV_LOG_DEBUG,   "BT_LOG", MESHLOG_FORMAT(D, format), ssv_log_timestamp(), "BT_LOG", ##__VA_ARGS__); }
#define LOG_VERBOSE(format, ... )           {if (LOG_LOCAL_LEVEL >= SSV_LOG_VERBOSE)  ssv_log_write(SSV_LOG_VERBOSE, "BT_LOG", MESHLOG_FORMAT(V, format), ssv_log_timestamp(), "BT_LOG", ##__VA_ARGS__); }

#if (LOG_LOCAL_LEVEL >= 4)
#define BLE_MESH_LOG_LOCAL_LEVEL_MAPPING    (LOG_LOCAL_LEVEL + 1)
#else
#define BLE_MESH_LOG_LOCAL_LEVEL_MAPPING    LOG_LOCAL_LEVEL
#endif

#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif /* MAX(a, b) */

#define BLE_MESH_LOG_LEVEL_CHECK(LAYER, LEVEL) (MAX(LAYER##_LOG_LEVEL, BLE_MESH_LOG_LOCAL_LEVEL_MAPPING) >= LOG_LEVEL_##LEVEL)

#define BLE_MESH_PRINT_E(tag, format, ...)   {ssv_log_write(SSV_LOG_ERROR,   tag, MESHLOG_FORMAT(E, format), ssv_log_timestamp(), tag, ##__VA_ARGS__); }
#define BLE_MESH_PRINT_W(tag, format, ...)   {ssv_log_write(SSV_LOG_WARN,    tag, MESHLOG_FORMAT(W, format), ssv_log_timestamp(), tag, ##__VA_ARGS__); }
#define BLE_MESH_PRINT_I(tag, format, ...)   {ssv_log_write(SSV_LOG_INFO,    tag, MESHLOG_FORMAT(I, format), ssv_log_timestamp(), tag, ##__VA_ARGS__); }
#define BLE_MESH_PRINT_D(tag, format, ...)   {ssv_log_write(SSV_LOG_DEBUG,   tag, MESHLOG_FORMAT(D, format), ssv_log_timestamp(), tag, ##__VA_ARGS__); }
#define BLE_MESH_PRINT_V(tag, format, ...)   {ssv_log_write(SSV_LOG_VERBOSE, tag, MESHLOG_FORMAT(V, format), ssv_log_timestamp(), tag, ##__VA_ARGS__); }

#define printk          printf

#define _STRINGIFY(x)   #x
#define STRINGIFY(s)    _STRINGIFY(s)

#ifndef __ASSERT
#define __ASSERT(test, fmt, ...)                        \
    do {                                                \
        if (!(test)) {                                  \
            printk("ASSERTION FAIL [%s] @ %s:%d:\n\t",  \
                   _STRINGIFY(test),                    \
                   __FILE__,                            \
                   __LINE__);                           \
            printk(fmt, ##__VA_ARGS__);                 \
            for (;;);                                   \
        }                                               \
    } while ((0))
#endif

#ifndef __ASSERT_NO_MSG
#define __ASSERT_NO_MSG(x)   do { if (!(x)) BLE_MESH_PRINT_E(MESH_TRACE_TAG, "error %s %u", __FILE__, __LINE__); } while (0)
#endif

void ssv_log_level_set_core(uint8_t level);
extern uint8_t g_loglevelcore;

#if !CONFIG_BLE_MESH_NO_LOG/* MESH_LOG_LEVEL */
#define BT_ERR(fmt, args...)    do {if ((g_loglevelcore >= LOG_LEVEL_ERROR) /*&& BLE_MESH_LOG_LEVEL_CHECK(MESH, ERROR)*/) BLE_MESH_PRINT_E(MESH_TRACE_TAG, fmt, ## args);} while(0)
#define BT_WARN(fmt, args...)   do {if ((g_loglevelcore >= LOG_LEVEL_WARN) /*&& BLE_MESH_LOG_LEVEL_CHECK(MESH, WARN)*/) BLE_MESH_PRINT_W(MESH_TRACE_TAG, fmt, ## args);} while(0)
#define BT_INFO(fmt, args...)   do {if ((g_loglevelcore >= LOG_LEVEL_INFO) /*&& BLE_MESH_LOG_LEVEL_CHECK(MESH, INFO)*/) BLE_MESH_PRINT_I(MESH_TRACE_TAG, fmt, ## args);} while(0)
#define BT_DBG(fmt, args...)    do {if ((g_loglevelcore >= LOG_LEVEL_DEBUG) /*&& BLE_MESH_LOG_LEVEL_CHECK(MESH, DEBUG)*/) BLE_MESH_PRINT_D(MESH_TRACE_TAG, fmt, ## args);} while(0)
#else
#define BT_ERR(fmt, args...)
#define BT_WARN(fmt, args...)
#define BT_INFO(fmt, args...)
#define BT_DBG(fmt, args...)
#endif

#if defined(CONFIG_BLE_MESH_NET_BUF_LOG) && (!CONFIG_BLE_MESH_NO_LOG)
#define NET_BUF_ERR(fmt, args...)   do {if ((NET_BUF_LOG_LEVEL >= LOG_LEVEL_ERROR) && BLE_MESH_LOG_LEVEL_CHECK(NET_BUF, ERROR)) BLE_MESH_PRINT_E(MESH_TRACE_TAG, fmt, ## args);} while(0)
#define NET_BUF_WARN(fmt, args...)  do {if ((NET_BUF_LOG_LEVEL >= LOG_LEVEL_WARN) && BLE_MESH_LOG_LEVEL_CHECK(NET_BUF, WARN)) BLE_MESH_PRINT_W(MESH_TRACE_TAG, fmt, ## args);} while(0)
#define NET_BUF_INFO(fmt, args...)  do {if ((NET_BUF_LOG_LEVEL >= LOG_LEVEL_INFO) && BLE_MESH_LOG_LEVEL_CHECK(NET_BUF, INFO)) BLE_MESH_PRINT_I(MESH_TRACE_TAG, fmt, ## args);} while(0)
#define NET_BUF_DBG(fmt, args...)   do {if ((NET_BUF_LOG_LEVEL >= LOG_LEVEL_DEBUG) && BLE_MESH_LOG_LEVEL_CHECK(NET_BUF, DEBUG)) BLE_MESH_PRINT_D(MESH_TRACE_TAG, fmt, ## args);} while(0)
#define NET_BUF_ASSERT(cond)        ASSERT(cond)//__ASSERT_NO_MSG(cond)
#else
#define NET_BUF_ERR(fmt, args...)
#define NET_BUF_WARN(fmt, args...)
#define NET_BUF_INFO(fmt, args...)
#define NET_BUF_DBG(fmt, args...)
#define NET_BUF_ASSERT(cond)
#endif

#if defined(CONFIG_BLE_MESH_NET_BUF_SIMPLE_LOG) && (!CONFIG_BLE_MESH_NO_LOG)
#define NET_BUF_SIMPLE_ERR(fmt, args...)    do {if ((NET_BUF_LOG_LEVEL >= LOG_LEVEL_ERROR) && BLE_MESH_LOG_LEVEL_CHECK(NET_BUF, ERROR)) BLE_MESH_PRINT_E(MESH_TRACE_TAG, fmt, ## args);} while(0)
#define NET_BUF_SIMPLE_WARN(fmt, args...)   do {if ((NET_BUF_LOG_LEVEL >= LOG_LEVEL_WARN) && BLE_MESH_LOG_LEVEL_CHECK(NET_BUF, WARN)) BLE_MESH_PRINT_W(MESH_TRACE_TAG, fmt, ## args);} while(0)
#define NET_BUF_SIMPLE_INFO(fmt, args...)   do {if ((NET_BUF_LOG_LEVEL >= LOG_LEVEL_INFO) && BLE_MESH_LOG_LEVEL_CHECK(NET_BUF, INFO)) BLE_MESH_PRINT_I(MESH_TRACE_TAG, fmt, ## args);} while(0)
#define NET_BUF_SIMPLE_DBG(fmt, args...)    do {if ((NET_BUF_LOG_LEVEL >= LOG_LEVEL_DEBUG) && BLE_MESH_LOG_LEVEL_CHECK(NET_BUF, DEBUG)) BLE_MESH_PRINT_D(MESH_TRACE_TAG, fmt, ## args);} while(0)
#define NET_BUF_SIMPLE_ASSERT(cond)         __ASSERT_NO_MSG(cond)
#else
#define NET_BUF_SIMPLE_ERR(fmt, args...)
#define NET_BUF_SIMPLE_WARN(fmt, args...)
#define NET_BUF_SIMPLE_INFO(fmt, args...)
#define NET_BUF_SIMPLE_DBG(fmt, args...)
#define NET_BUF_SIMPLE_ASSERT(cond)
#endif

#endif /* _BLE_MESH_TRACE_H_ */
