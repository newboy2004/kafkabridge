#ifndef QBUS_CONSUMER_H_
#define QBUS_CONSUMER_H_

#include <stdio.h>
#include <stdint.h>

#include "qbus_result.h"

#ifdef __cplusplus
extern "C" {
#endif
//-------------------------------------------------------------
typedef void* QbusCommitOffsetInfoType;
typedef void* QbusConsumerHandle;
typedef void (*QbusConsumerDeliveryFuncType)(const char* topic,
            const char* msg,
            int64_t msg_len);
typedef void (*QbusConsumerDeliveryForCommitOffsetFuncType)(const char* topic,
            const char* msg,
            int64_t msg_len,
            const QbusCommitOffsetInfoType offset_info);

typedef struct tagQbusConsumerCallbackInfo {
    QbusConsumerDeliveryFuncType callback;
    QbusConsumerDeliveryForCommitOffsetFuncType callback_for_commit_offset;
} QbusConsumerCallbackInfo;
//-------------------------------------------------------------
QbusConsumerHandle NewQbusConsumer();

void DeleteQbusConsumer(QbusConsumerHandle handle);

QbusResult InitQbusConsumer(QbusConsumerHandle handle,
            const char* cluster_name,
            const char* log_path,
            const char* config_path,
            QbusConsumerDeliveryFuncType callback);

QbusResult InitQbusConsumerEx(QbusConsumerHandle handle,
            const char* cluster_name,
            const char* log_path,
            const char* config_path,
            QbusConsumerCallbackInfo callback_info);

QbusResult QbusConsumerSubscribeOne(QbusConsumerHandle handle,
            const char* group,
            const char* topic);

QbusResult QbusConsumerSubscribe(QbusConsumerHandle handle,
            const char* group,
            const char* topics[],
            int32_t topics_count);

QbusResult QbusConsumerStart(QbusConsumerHandle handle);

void QbusConsumerCommitOffset(QbusConsumerHandle handle,
            QbusCommitOffsetInfoType offset_info);

void QbusConsumerStop(QbusConsumerHandle handle);

#ifdef __cplusplus
}//extern "C" {
#endif

#endif//#ifndef QBUS_CONSUMER_H_
