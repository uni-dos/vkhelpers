/*
 * Copyright (c) 2018-2022 Jean-Philippe Bruyère <jp_bruyere@hotmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the
 * Software, and to permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include "vkh_queue.h"
#include "vkh_device.h"
#include "vkh_phyinfo.h"

VkhQueue _init_queue (VkhDevice dev) {
	VkhQueue q	= (vkh_queue_t*)calloc(1, sizeof(vkh_queue_t));
	q->dev = dev;
	return q;
}


VkhQueue vkh_queue_create (VkhDevice dev, uint32_t familyIndex, uint32_t qIndex) {
	VkhQueue q	= _init_queue (dev);
	q->familyIndex	= familyIndex;
	vkGetDeviceQueue (dev->dev, familyIndex, qIndex, &q->queue);
	return q;
}

//VkhQueue vkh_queue_find (VkhDevice dev, VkQueueFlags flags) {

//	  return q;
//}
/*void vkh_queue_submit(VkhQueue queue, VkCommandBuffer *pCmdBuff, VkFence fence, VkSemaphore signal){
	VkPipelineStageFlags stageFlags = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT;
	VkSubmitInfo submit_info = { .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
								 .pWaitDstStageMask = &stageFlags,
								 .commandBufferCount = 1,
								 .pCommandBuffers = pCmdBuff};

	VkSemaphore wait = queue->lastSubmissionSemaphore;
	queue->lastSubmissionSemaphore = signal;

	if (wait) {
		submit_info.waitSemaphoreCount = 1;
		submit_info.pWaitSemaphores = &wait;
	}
	if (signal) {
		submit_info.signalSemaphoreCount = 1;
		submit_info.pSignalSemaphores = &queue->lastSubmissionSemaphore;
	}

	VK_CHECK_RESULT(vkQueueSubmit(queue->queue, 1, &submit_info, fence));
}*/
VkResult vkh_queue_wait_idle (VkhQueue queue){
	return vkQueueWaitIdle (queue->queue);
}

void vkh_queue_destroy (VkhQueue queue){
	free (queue);
}
