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
  hardware* initH;
  hardware* hardware_1 = (hardware*)malloc(sizeof(hardware));
}

void TearDown()
{
  //free(hardware_1);
}

TEST(createNullDMTest, create_nullDM){
  ASSERT_EQ( strcmp(create_nullDM()->ip, (char*)"none"), 0);
}

TEST(init_hardware_test, init_hardware){
  hardware initH = *init_hardware(&initH);
  ASSERT_EQ(initH.dim, 0);
}

TEST(init_DM_Test, init_DM){
  DM tmpDM = *init_DM(&tmpDM);
  ASSERT_EQ(tmpDM.size, 0);
  ASSERT_EQ(tmpDM.status, 0);
}

TEST(init_network_test, init_network){
  network tmpNet = *init_network(&tmpNet);
  ASSERT_EQ(tmpNet.size, 0);
}

TEST(DM_test_methods_1, create_DM){
  DM tmpDM = *init_DM(&tmpDM);
  create_DM(&tmpDM, (char*)"127.0.0.1", (char*)"255.255.255.0");
  ASSERT_EQ(strcmp(tmpDM.ip, (char*)"127.0.0.1"), 0);
  ASSERT_EQ(strcmp(tmpDM.subnet_mask, (char*)"255.255.255.0"), 0);
}

TEST(network_method_test_1, add_DM_to_net){
  network tmpNet = *init_network(&tmpNet);
  DM tmpDM = *init_DM(&tmpDM);
  create_DM(&tmpDM, (char*)"127.0.0.1", (char*)"255.255.255.0");
  add_DM_to_net(tmpDM, &tmpNet);
  ASSERT_EQ(strcmp(tmpNet.things[0].ip, (char*)"127.0.0.1"), 0);
  ASSERT_EQ(strcmp(tmpNet.things[0].subnet_mask, (char*)"255.255.255.0"), 0);

}

TEST(hardware_test_methods_1, set_object_dim){
    hardware hware = *init_hardware(&hware);
    set_object_dim(&hware, 10);
    ASSERT_EQ(hware.dim, 10);
}

TEST(hardware_test_methods_2, set_object_name){
  hardware hware = *init_hardware(&hware);
  set_object_name(&hware, (char*)"test");
  ASSERT_EQ(strcmp(hware.name, (char*)"test"), 0);
}

TEST(hardware_test_methods_3, set_object_type){
  hardware hware = *init_hardware(&hware);
  set_object_type(&hware, (char*)"bulb");
  ASSERT_EQ(strcmp(hware.type, (char*)"bulb"), 0);
}

TEST(hardware_test_methods_4, set_object_color){
  hardware hware = *init_hardware(&hware);
  set_object_color(&hware, (char*)"blue");
  ASSERT_EQ(strcmp(hware.color, (char*)"blue"), 0);
}

TEST(hardware_test_methods_5, set_object_state){
  hardware hware = *init_hardware(&hware);
  set_object_state(&hware, (char*)"True");
  ASSERT_EQ(strcmp(hware.state, (char*)"True"), 0);
}

TEST(hardware_test_methods_6, hardware_copy_new){
  hardware hware = *init_hardware(&hware);
  hardware hware2 = *init_hardware(&hware2);
  set_object_state(&hware, (char*)"True");
  set_object_color(&hware, (char*)"blue");
  set_object_type(&hware, (char*)"bulb");
  set_object_name(&hware, (char*)"test");
  set_object_dim(&hware, 10);
  hardware_copy_new(&hware2, &hware);
  ASSERT_EQ(strcmp(hware2.state, (char*)"True"), 0);
  ASSERT_EQ(strcmp(hware2.type, (char*)"bulb"), 0);
  ASSERT_EQ(strcmp(hware2.color, (char*)"blue"), 0);
  ASSERT_EQ(strcmp(hware2.name, (char*)"test"), 0);
  ASSERT_EQ(hware2.dim, 10);
}

TEST(hardware_test_replace_methods_1, set_new_object_name){
  hardware hware = *init_hardware(&hware);
  set_object_name(&hware, (char*)"test");
  set_new_object_name(&hware, (char*)"tester");
  ASSERT_EQ(strcmp(hware.name, (char*)"tester"), 0);
}

TEST(hardware_test_replace_methods_2, set_new_object_type){
  hardware hware = *init_hardware(&hware);
  set_object_type(&hware, (char*)"bulb");
  set_new_object_type(&hware, (char*)"bulbor");
  ASSERT_EQ(strcmp(hware.type, (char*)"bulbor"), 0);
}

TEST(hardware_test_replace_methods_3, set_new_object_color){
  hardware hware = *init_hardware(&hware);
  set_object_color(&hware, (char*)"blue");
  set_new_object_color(&hware, (char*)"bluer");
  ASSERT_EQ(strcmp(hware.color, (char*)"bluer"), 0);
}

TEST(hardware_test_replace_methods_4, set_new_object_state){
  hardware hware = *init_hardware(&hware);
  set_object_state(&hware, (char*)"True");
  set_new_object_state(&hware, (char*)"Truer");
  ASSERT_EQ(strcmp(hware.state, (char*)"Truer"), 0);
}

TEST(hardware_test_replace_methods_5, hardware_copy_replace){
  hardware hware = *init_hardware(&hware);
  hardware hware2 = *init_hardware(&hware2);
  set_object_state(&hware, (char*)"Truer");
  set_object_color(&hware, (char*)"bluer");
  set_object_type(&hware, (char*)"bulbor");
  set_object_name(&hware, (char*)"tester");
  
  set_object_state(&hware2, (char*)"True");
  set_object_color(&hware2, (char*)"blue");
  set_object_type(&hware2, (char*)"bulb");
  set_object_name(&hware2, (char*)"test");

  hardware_copy_replace(&hware2, &hware);
  ASSERT_EQ(strcmp(hware2.state, (char*)"Truer"), 0);
  ASSERT_EQ(strcmp(hware2.type, (char*)"bulbor"), 0);
  ASSERT_EQ(strcmp(hware2.color, (char*)"bluer"), 0);
  ASSERT_EQ(strcmp(hware2.name, (char*)"tester"), 0);
}

TEST(DM_test_methods_2, add_to_DM){
  hardware hware = *init_hardware(&hware);
  set_object_state(&hware, (char*)"True");
  set_object_color(&hware, (char*)"blue");
  set_object_type(&hware, (char*)"bulb");
  set_object_name(&hware, (char*)"test");
  set_object_dim(&hware, 10);
  DM tmpDM = *init_DM(&tmpDM);
  create_DM(&tmpDM, (char*)"127.0.0.1", (char*)"255.255.255.0");
  add_to_DM(&tmpDM, &hware);
  ASSERT_EQ(strcmp(tmpDM.objects[0].state, (char*)"True"), 0);
  ASSERT_EQ(strcmp(tmpDM.objects[0].type, (char*)"bulb"), 0);
  ASSERT_EQ(strcmp(tmpDM.objects[0].color, (char*)"blue"), 0);
  ASSERT_EQ(strcmp(tmpDM.objects[0].name, (char*)"test"), 0);
  ASSERT_EQ(tmpDM.objects[0].dim, 10);

}

TEST(createQueueTest, createQueue)
{
  queue* temp = createQueue(2);
  ASSERT_EQ(-1, strComp(temp->head->currentWord, (char*)"\0"));
}

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
  SetUp();
  testing::InitGoogleTest(&argc, args);
  return RUN_ALL_TESTS();
}
