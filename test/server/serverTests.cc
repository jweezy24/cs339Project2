#include <gtest/gtest.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "../../src/server/queueStruct.c"
#include "../../src/server/messageReader.c"


void SetUp()
{

}

void TearDown()
{

}


//Cleared 10/8/18
TEST(createQueueTest, createQueue)
{
  queue* temp = createQueue(2);
  ASSERT_EQ(-1, strComp(temp->head->currentWord, (char*)"\0"));
}

//Cleared 10/8/18
TEST(enqueueTest, enqueue)
{
  queue* temp = createQueue(2);
  node* testNode = (node*)malloc(sizeof(node));
  testNode->currentWord = (char*)"test";
  enqueue(temp, testNode->currentWord);
  ASSERT_EQ(-1, strComp(temp->head->currentWord, (char*)"test"));
  ASSERT_EQ(-1, strComp(temp->tail->currentWord, (char*)"\0"));

}

TEST(dequeueTest, dequeue)
{
  queue* temp = createQueue(2);
  node* testNode = (node*)malloc(sizeof(node));
  node* testNode2 = (node*)malloc(sizeof(node));
  node* returnNode = (node*)malloc(sizeof(node)*3);
  testNode2->currentWord = (char*)"test2";
  testNode->currentWord = (char*)"test";
  enqueue(temp, testNode->currentWord);
  enqueue(temp, testNode2->currentWord);
  returnNode = dequeue(temp);
  ASSERT_EQ(-1, strComp(returnNode->currentWord, (char*)"test"));
}

TEST(getAllElementsTest, getAllElements)
{
  queue* temp = createQueue(2);
  node* testNode = (node*)malloc(sizeof(node));
  node* testNode2 = (node*)malloc(sizeof(node));
  node* returnNode = (node*)malloc(sizeof(node)*3);
  testNode2->currentWord = (char*)"test2";
  testNode->currentWord = (char*)"test";
  enqueue(temp, testNode->currentWord);
  enqueue(temp, testNode2->currentWord);
  stringArray* tester = getAllElements(temp);
  ASSERT_EQ(-1, strComp(tester->words[0].word,(char*)"test"));
  ASSERT_EQ(-1, strComp(tester->words[1].word,(char*)"test2"));

}
//Queue length gets how many current elements are in the queue
TEST(queueLengthTest, queueLength)
{
  queue* tempQ = createQueue(2);
  node* testNode = (node*)malloc(sizeof(node));
  node* testNode2 = (node*)malloc(sizeof(node));
  testNode2->currentWord = (char*)"test2";
  testNode->currentWord = (char*)"test";
  enqueue(tempQ, testNode->currentWord);
  enqueue(tempQ, testNode2->currentWord);
  ASSERT_EQ(getQueueLength(tempQ), 2);
}


int main(int argc, char **args)
{
  testing::InitGoogleTest(&argc, args);
  return RUN_ALL_TESTS();
}
