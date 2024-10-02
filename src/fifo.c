#include "fifo.h"
#include "stdio.h"

void fifo_worker_handler(QueueHandle_t requests, QueueHandle_t results, int id)
{
    while(1)
    {
        struct request_msg receivedData;
        BaseType_t retStatus = xQueueReceive(requests, &receivedData, portMAX_DELAY);

        if( retStatus == pdPASS )
        {
                receivedData.output = receivedData.input + 5;
                receivedData.handled_by = id;

                BaseType_t resultStatus = xQueueSendToBack( results, &receivedData, 1000 );

                if( resultStatus != pdPASS )
                {
                    printf("Error adding item to results queue\n");
                }
        }
    }
}