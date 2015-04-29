/*
 * PriorityRoundRobin.cpp
 *
 *  Created on: Apr 15, 2015
 *      Author: Ryan Smith
 */

#include "Task.h"
#include <vector>
#include <queue>

/*Inserts a copy of a given Task into the appropriate queue.*/
void insertTask(std::vector<std::queue<Task>* >& queueSet, Task task){
	switch(task.priority){
	case 0:
		queueSet.at(0)->push(task);
		break;
	case 1:
		queueSet.at(1)->push(task);
		break;
	case 2:
		queueSet.at(2)->push(task);
		break;
	case 3:
		queueSet.at(3)->push(task);
		break;
	case 4:
		queueSet.at(4)->push(task);
		break;
	case 5:
		queueSet.at(5)->push(task);
		break;
	case 6:
		queueSet.at(6)->push(task);
		break;
	case 7:
		queueSet.at(7)->push(task);
		break;
	case 8:
		queueSet.at(8)->push(task);
		break;
	case 9:
		queueSet.at(9)->push(task);
		break;

	}
}

/*Returns True if there are remaining tasks in the queues, False otherwise.*/
bool remainingTasks(std::vector<std::queue<Task>* >& queueSet){
	std::vector<std::queue<Task>* >::iterator iter;
	for (iter = queueSet.begin(); iter != queueSet.end(); iter++){
		if (!(*iter)->empty())
			return true;
	}
	return false;
}

/*Returns a pointer to the highest priority task remaining in the queues.*/
Task* nextHighestPriorityTask(std::vector<std::queue<Task>* >& queueSet){
	if (!queueSet.at(9)->empty())
		return &queueSet.at(9)->front();
	else if (!queueSet.at(8)->empty())
		return &queueSet.at(8)->front();
	else if (!queueSet.at(7)->empty())
		return &queueSet.at(7)->front();
	else if (!queueSet.at(6)->empty())
		return &queueSet.at(6)->front();
	else if (!queueSet.at(5)->empty())
		return &queueSet.at(5)->front();
	else if (!queueSet.at(4)->empty())
		return &queueSet.at(4)->front();
	else if (!queueSet.at(3)->empty())
		return &queueSet.at(3)->front();
	else if (!queueSet.at(2)->empty())
		return &queueSet.at(2)->front();
	else if (!queueSet.at(1)->empty())
		return &queueSet.at(1)->front();
	else if (!queueSet.at(0)->empty())
		return &queueSet.at(0)->front();
	else
		return NULL;
}

/*Implements Priority Round Robin scheduling algorithm*/
void priority_roundrobin(std::vector<Task> processList, int slice) {
	int globalClock = 0; // keeps a global time reference
	Task* executingTask; // the Task that is currently allowed to execute
	int sliceRem = slice; // remaining time in the current quantum
	bool waitingForProcess = true; // indicates that CPU is ready for more processes but none are currently requesting execution
	int totalWaitTime = 0; // holds value to calculate average wait time

	//queues for each priority level, adds each to a vector<queue<Task>*>
	std::vector<std::queue<Task>* > queueSet;
	std::queue<Task> prior0; queueSet.push_back(&prior0);
	std::queue<Task> prior1; queueSet.push_back(&prior1);
	std::queue<Task> prior2; queueSet.push_back(&prior2);
	std::queue<Task> prior3; queueSet.push_back(&prior3);
	std::queue<Task> prior4; queueSet.push_back(&prior4);
	std::queue<Task> prior5; queueSet.push_back(&prior5);
	std::queue<Task> prior6; queueSet.push_back(&prior6);
	std::queue<Task> prior7; queueSet.push_back(&prior7);
	std::queue<Task> prior8; queueSet.push_back(&prior8);
	std::queue<Task> prior9; queueSet.push_back(&prior9);

	//this will advance the clock until the first task arrives. when this happens, all tasks arriving at that same time will
	//be inserted into their respective queues and the executingTask will be set at the highest priority of those
	  while (waitingForProcess){
		  std::vector<Task>::iterator iter;
		  //since priority is important, this will loop through all Tasks even after finding one in case one of higher priority arrives at same time
		  for (iter = processList.begin(); iter != processList.end(); ++iter){
		  		if (iter->arrival == globalClock){
		  			insertTask(queueSet, *iter);
		  			std::cout << globalClock << ": Adding task " << iter->name << std::endl;
		  			waitingForProcess = false;
		  		}
		  }
		  if (waitingForProcess){
			  std::cout << globalClock << ": Nothing running. " << std::endl;
			  globalClock++;
		  }
		  else {
	  			executingTask = nextHighestPriorityTask(queueSet);
	  			std::cout << globalClock << ": Running task " << executingTask->name << std::endl;
		  }
	  }

  // controls execution based on queues and slice
  while (remainingTasks(queueSet)) {
	  //higher priority task available
	  if (nextHighestPriorityTask(queueSet)->priority > executingTask->priority){
		  //put the current task at the end of its queue and remove it from the front
		  queueSet.at(executingTask->priority)->push(*executingTask);
		  queueSet.at(executingTask->priority)->pop();
		  std::cout << globalClock << ": Pre-empting task " << executingTask->name << std::endl;
		  //set executingTask to highest priority and reset slice
		  executingTask = nextHighestPriorityTask(queueSet);
		  std::cout << globalClock << ": Running task " << executingTask->name << std::endl;
		  sliceRem = slice;
	  }
	  //current task finished
	  else if (executingTask->remaining == 0){
		  //remove from front of its queue, update totalWaitTime
		  std::cout << globalClock << ": Finished task " << executingTask->name << std::endl;
		  queueSet.at(executingTask->priority)->pop();
		  totalWaitTime += (globalClock - executingTask->arrival - executingTask->time);
		  //if there are more tasks in the queues, update to the next highest priority and reset slice
		  if (remainingTasks(queueSet)){
			  executingTask = nextHighestPriorityTask(queueSet);
			  std::cout << globalClock << ": Running task " << executingTask->name << std::endl;
			  sliceRem = slice;
		  }
	  }
	  //slice finished
	  else if (sliceRem == 0){
		  std::cout << globalClock << ": Time slice done for task " << executingTask->name << std::endl;
		  queueSet.at(executingTask->priority)->push(*executingTask);
		  queueSet.at(executingTask->priority)->pop();
		  executingTask = nextHighestPriorityTask(queueSet);
		  std::cout << globalClock << ": Running task " << executingTask->name << std::endl;
		  sliceRem = slice;
	  }
	  //this handles normal progression: clock updated, task time remaining and slice reduced.
	  executingTask->remaining--;
	  sliceRem--;
	  globalClock++;

	  //load all new arrivals after clock update
	  std::vector<Task>::iterator iter;
	  for (iter = processList.begin(); iter != processList.end(); ++iter){
			if (iter->arrival == globalClock){
				insertTask(queueSet, *iter);
				std::cout << globalClock << ": Adding task " << iter->name << std::endl;
			}
	  }
  }
  std::cout << "All tasks finished." << std::endl;
  std::cout << "Total wait time: " << (double) totalWaitTime / (double) processList.size();

}





