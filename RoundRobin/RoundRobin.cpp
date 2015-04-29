/*
 * RoundRobin.cpp
 *
 *  Created on: Apr 15, 2015
 *      Author: Ryan Smith
 */

#include "Task.h"
#include <vector>
#include <queue>
#include <iterator>

void roundrobin(std::vector<Task> processList, unsigned int quantum) {

  int globalClock = 0; // keeps a global time reference
  Task executingTask; // the Task that is currently allowed to execute
  int quantumRem = quantum; // remaining time in the current quantum
  std::queue<Task> processQueue; // the queue of processes that would like to execute
  bool waitingForProcess = true; // indicates that CPU is ready for more processes but none are currently requesting execution
  int totalWaitTime = 0; // holds value to calculate average wait time

  //this will advance the clock until a task has been inserted into the queue
  while (waitingForProcess){
	  std::vector<Task>::iterator iter;
	  for (iter = processList.begin(); iter != processList.end(); ++iter){
	  		if (iter->arrival == globalClock){
	  			processQueue.push(*iter);
	  			executingTask = processQueue.front();
	  			std::cout << globalClock << ": Adding task " << executingTask.name << std::endl;
	  			std::cout << globalClock << ": Running task " << executingTask.name << std::endl;
	  			waitingForProcess = false;
	  			break;
	  		}
	  }
	  if (waitingForProcess){
		  std::cout << globalClock << ": Nothing running. " << std::endl;
		  globalClock++;
	  }
  }

  // controls execution based on processQueue and quantumRem
  while (!processQueue.empty()) {
	  //check arrival times against globalClock, add process to processQueue and remove from processList upon arrival
	  if (!processList.empty()){
		  std::vector<Task>::iterator iter;
		  for (iter = processList.begin(); iter != processList.end(); ++iter){
				if (iter->arrival == globalClock && iter->name != executingTask.name){
					processQueue.push(*iter);
					std::cout << globalClock << ": Adding task " << iter->name << std::endl;
				}
		  }
	  }
	  //if the executingTask has finished, remove it and update executingTask to next in processQueue
	  if (executingTask.remaining == 0){
		  std::cout << globalClock << ": Finished task " << executingTask.name << std::endl;
		  totalWaitTime += (globalClock - executingTask.arrival - executingTask.time);
		  processQueue.pop();
		  if (!processQueue.empty()){
			  executingTask = processQueue.front();
			  std::cout << globalClock << ": Running task " << executingTask.name << std::endl;
			  quantumRem = quantum;
		  }
	  }
	  //if quantum has finished, move the executingTask from the front to the back of the queue, then update with next in queue
	  else if (quantumRem == 0){
		  std::cout << globalClock << ": Time slice done for task " << executingTask.name << std::endl;
		  processQueue.push(executingTask);
		  processQueue.pop();
		  executingTask = processQueue.front();
		  std::cout << globalClock << ": Running task " << executingTask.name << std::endl;
		  quantumRem = quantum;
	  }
	  //this handles normal progression: clock updated, task time remaining and quantum reduced.
	  executingTask.remaining--;
	  quantumRem--;
	  globalClock++;
  }
  std::cout << "All tasks finished." << std::endl;
  std::cout << "Total wait time: " << totalWaitTime / processList.size();

}



