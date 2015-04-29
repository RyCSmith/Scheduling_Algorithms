/*
 * main.cpp
 *
 *  Created on: Apr 2, 2015
 *      Author: Ryan Smith
 */


#include <iostream>
#include <vector>
#include <string>
#include "Task.h"

extern void roundrobin(std::vector<Task>, unsigned int);

int main() {

  Task *t0 = new Task;
  t0->name = "bert";
  t0->arrival = 2;
  t0->time = 11;
  t0->remaining = 11;

  Task *t1 = new Task;
  t1->name = "ernie";
  t1->arrival = 0;
  t1->time = 8;
  t1->remaining = 8;

  Task *t2 = new Task;
  t2->name = "oscar";
  t2->arrival = 12;
  t2->time = 20;
  t2->remaining = 20;

  Task *t3 = new Task;
  t3->name = "grover";
  t3->arrival = 7;
  t3->time = 15;
  t3->remaining = 15;

  Task *t4 = new Task;
  t4->name = "elmo";
  t4->arrival = 10;
  t4->time = 4;
  t4->remaining = 4;

  std::vector<Task> tasks;

  tasks.push_back(*t0);
  tasks.push_back(*t1);
  tasks.push_back(*t2);
  tasks.push_back(*t3);
  tasks.push_back(*t4);

  roundrobin(tasks, 8);

  delete t0;
  delete t1;
  delete t2;
  delete t3;
  delete t4;

  return 1;
}

