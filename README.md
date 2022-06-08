## Dining Philosophers Problem using Network Calls in Distributed Systems
--------------------------------------------------

This program demonstrates a solution to Dining Philosophers's Problem using Message Passing as the only means of communication.

## What is Dining Philosopher Problem?

Five philosophers, live in a house and dine at the same table. Each philosopher has their own place at the table. Their only problem aside from those of philosophy, is that the dish served is a kind of spaghetti, that has to be eaten with two forks. There is a fork between each plate.

Each philosopher will alternately think and eat. However, a philosopher can only eat the spaghetti when they have both a left and right fork. Two forks will only be available when their two nearest neighbors are thinking, not eating. After an individual philosopher finishes eating, they will put down both forks.

The problem is how to design a discipline of behavior (a concurrent algorithm) such that no philosopher will starve; i.e., each can forever continue to alternate between eating and thinking, assuming that no philosopher can know when others may want to eat or think.

Read more about the problem from [this Wikipedia article](https://en.wikipedia.org/wiki/Dining_philosophers_problem).

## Program Description

a. Create five child processes for philosophers, and five child processes for each of the chopsticks.

b. Initiate a pair of sockets for each connection to a server

c. Avoid possible deadlock

d. Close and unlink the sockets.

Description: Use the fork( ) system call to create a child process. The parent should do nothing but create ten child processes. The requests for granting and releasing chopsticks should be done by each child process representing a philosopher through communication with the two processes representing the philosopher’s left and right hand chopsticks.TCP/IP should be used for communication between philosophers and chopstick processes. The datagram type of sockets should be employed between the parent and child processes including both the philosopher and chopstick processes. Use write( ) and read() system calls with the connection-oriented communication. A solution that prevents deadlock or starvation should be implemented. For example the RightLeftDP algorithm (Lynch,1996) is a suitable algorithm. Five child processes are to be created for the five philosophers. The philosophers change their states among “thinking”, “waiting”, and “eating” until all philosophers fulfil their eating requirements(60 seconds total eating time). Print the status of each philosopher whenever there is a change in the status.

## Requirements
gcc

## Running the Program
```sh
$ gcc main.c
```

## Acknowledgement
I would like to thank [Jini Raju](https://www.tkmce.ac.in/staff-profile.php?id=460&slug=jini-raju) for assigning this project to me.
