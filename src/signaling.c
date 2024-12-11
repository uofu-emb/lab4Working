#include "signaling.h"

void signal_handle_calculation(SemaphoreHandle_t request,
                               SemaphoreHandle_t response,
                               struct signal_data *data)
{
    //Take request, will wait forever for the semaphore right now
    BaseType_t retStatus = xSemaphoreTake(request, portMAX_DELAY);
    if( retStatus == pdPASS )
    {
        data->output = data->input+5;
    }
    xSemaphoreGive(response);
}

BaseType_t signal_request_calculate(SemaphoreHandle_t request,
                                    SemaphoreHandle_t response,
                                    struct signal_data *data)
{
    //Give the request semaphore
    xSemaphoreGive(request);

    BaseType_t retStatus = xSemaphoreTake(response, 1000);
    
    return retStatus;
}