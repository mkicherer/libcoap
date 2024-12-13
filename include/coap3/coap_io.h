/*
 * coap_io.h -- Default network I/O functions for libcoap
 *
 * Copyright (C) 2012-2013,2024 Olaf Bergmann <bergmann@tzi.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * This file is part of the CoAP library libcoap. Please see README for terms
 * of use.
 */

/**
 * @file coap_io.h
 * @brief Default network I/O functions
 */

#ifndef COAP_IO_H_
#define COAP_IO_H_

#include <sys/types.h>

#include "coap_address.h"

#ifdef RIOT_VERSION
#include "net/gnrc.h"
#endif /* RIOT_VERSION */

#ifndef COAP_RXBUFFER_SIZE
#define COAP_RXBUFFER_SIZE 1472
#endif /* COAP_RXBUFFER_SIZE */

/*
 * It may may make sense to define this larger on busy systems
 * (lots of sessions, large number of which are active), by using
 * -DCOAP_MAX_EPOLL_EVENTS=nn at compile time.
 */
#ifndef COAP_MAX_EPOLL_EVENTS
#define COAP_MAX_EPOLL_EVENTS 10
#endif /* COAP_MAX_EPOLL_EVENTS */

#ifdef _WIN32
typedef SOCKET coap_fd_t;
#define coap_closesocket closesocket
#define COAP_SOCKET_ERROR SOCKET_ERROR
#define COAP_INVALID_SOCKET INVALID_SOCKET
#else
typedef int coap_fd_t;
#define coap_closesocket close
#define COAP_SOCKET_ERROR (-1)
#define COAP_INVALID_SOCKET (-1)
#endif

typedef uint16_t coap_socket_flags_t;
#define COAP_SOCKET_EMPTY        0x0000  /**< the socket is not used */
#define COAP_SOCKET_NOT_EMPTY    0x0001  /**< the socket is not empty */
#define COAP_SOCKET_BOUND        0x0002  /**< the socket is bound */
#define COAP_SOCKET_CONNECTED    0x0004  /**< the socket is connected */
#define COAP_SOCKET_WANT_READ    0x0010  /**< non blocking socket is waiting for reading */
#define COAP_SOCKET_WANT_WRITE   0x0020  /**< non blocking socket is waiting for writing */
#define COAP_SOCKET_WANT_ACCEPT  0x0040  /**< non blocking server socket is waiting for accept */
#define COAP_SOCKET_WANT_CONNECT 0x0080  /**< non blocking client socket is waiting for connect */
#define COAP_SOCKET_CAN_READ     0x0100  /**< non blocking socket can now read without blocking */
#define COAP_SOCKET_CAN_WRITE    0x0200  /**< non blocking socket can now write without blocking */
#define COAP_SOCKET_CAN_ACCEPT   0x0400  /**< non blocking server socket can now accept without blocking */
#define COAP_SOCKET_CAN_CONNECT  0x0800  /**< non blocking client socket can now connect without blocking */
#define COAP_SOCKET_MULTICAST    0x1000  /**< socket is used for multicast communication */

typedef struct coap_addr_tuple_t {
  coap_address_t remote;       /**< remote address and port */
  coap_address_t local;        /**< local address and port */
} coap_addr_tuple_t;

const char *coap_socket_strerror(void);

typedef enum {
  COAP_NACK_TOO_MANY_RETRIES,
  COAP_NACK_NOT_DELIVERABLE,
  COAP_NACK_RST,
  COAP_NACK_TLS_FAILED,
  COAP_NACK_ICMP_ISSUE,
  COAP_NACK_BAD_RESPONSE,
  COAP_NACK_TLS_LAYER_FAILED,
  COAP_NACK_WS_LAYER_FAILED,
  COAP_NACK_WS_FAILED
} coap_nack_reason_t;

#endif /* COAP_IO_H_ */
