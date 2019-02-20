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

TEST(network_method_test_2, DM_status_watch){
  DM tmpDM = *init_DM(&tmpDM);
  network tmpNet = *init_network(&tmpNet);
  create_DM(&tmpDM, (char*)"127.0.0.1", (char*)"255.255.255.0");
  add_DM_to_net(tmpDM, &tmpNet);
  tmpNet = *DM_status_watch(&tmpNet, (char*)"none");
  ASSERT_EQ(tmpNet.things[0].status, -1);
}

TEST(network_method_test_3, remove_from_network ){
  DM tmpDM = *init_DM(&tmpDM);
  network tmpNet = *init_network(&tmpNet);
  create_DM(&tmpDM, (char*)"127.0.0.1", (char*)"255.255.255.0");
  add_DM_to_net(tmpDM, &tmpNet);
  tmpNet = remove_from_network(&tmpNet, &tmpDM);
  ASSERT_EQ(tmpNet.size, 0);
}

TEST(network_method_test_4, get_DM_IP){
  DM tmpDM = *init_DM(&tmpDM);
  network tmpNet = *init_network(&tmpNet);
  create_DM(&tmpDM, (char*)"127.0.0.1", (char*)"255.255.255.0");
  add_DM_to_net(tmpDM, &tmpNet);
  DM testDMGood = *get_DM_IP(&tmpNet, (char*)"127.0.0.1");
  DM testDMBad = *get_DM_IP(&tmpNet, (char*)"garbage");
  ASSERT_EQ(strcmp(testDMGood.ip, (char*)"127.0.0.1"), 0);
  ASSERT_EQ(strcmp(testDMBad.ip, (char*)"none"), 0);
}

TEST(network_method_test_5, get_DM_Index){
  DM tmpDM = *init_DM(&tmpDM);
  network tmpNet = *init_network(&tmpNet);
  create_DM(&tmpDM, (char*)"127.0.0.1", (char*)"255.255.255.0");
  add_DM_to_net(tmpDM, &tmpNet);
  ASSERT_EQ(get_DM_Index(&tmpNet,(char*) "127.0.0.1"), 0);
  ASSERT_EQ(get_DM_Index(&tmpNet,(char*) "garbage"), -1);
}

TEST(network_method_test_6, check_if_DM){
  DM tmpDM = *init_DM(&tmpDM);
  network tmpNet = *init_network(&tmpNet);
  create_DM(&tmpDM, (char*)"127.0.0.1", (char*)"255.255.255.0");
  add_DM_to_net(tmpDM, &tmpNet);
  ASSERT_EQ(check_if_DM(&tmpNet,(char*) "127.0.0.1"), 0);
  ASSERT_EQ(check_if_DM(&tmpNet,(char*) "garbage"), 1);
}

TEST(DM_test_methods_3, remove_from_dm){
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
  tmpDM = *remove_from_dm(&tmpDM, &hware);
  ASSERT_EQ(tmpDM.size, 0);
}

TEST(DM_test_methods_4, update_status){
  DM tmpDM = *init_DM(&tmpDM);
  create_DM(&tmpDM, (char*)"127.0.0.1", (char*)"255.255.255.0");
  tmpDM.status = -1;
  update_status(&tmpDM);
  ASSERT_EQ(tmpDM.status, 0);
}

TEST(DM_test_methods_5, name_check){
  hardware hware = *init_hardware(&hware);
  set_object_state(&hware, (char*)"True");
  set_object_color(&hware, (char*)"blue");
  set_object_type(&hware, (char*)"bulb");
  set_object_name(&hware, (char*)"test");
  set_object_dim(&hware, 10);
  hardware hware2 = *init_hardware(&hware);
  set_object_state(&hware2, (char*)"True");
  set_object_color(&hware2, (char*)"blue");
  set_object_type(&hware2, (char*)"bulb");
  set_object_name(&hware2, (char*)"aye");
  set_object_dim(&hware2, 10);
  DM tmpDM = *init_DM(&tmpDM);
  create_DM(&tmpDM, (char*)"127.0.0.1", (char*)"255.255.255.0");
  add_to_DM(&tmpDM, &hware);
  add_to_DM(&tmpDM, &hware2);
  ASSERT_EQ(name_check(&tmpDM, (char*)"test"), 0);
  ASSERT_EQ(name_check(&tmpDM, (char*)"aye"), 0);
  ASSERT_EQ(name_check(&tmpDM, (char*)"yo"), 1);
}

TEST(DM_test_methods_6, get_hardware_name){
  hardware hware = *init_hardware(&hware);
  set_object_state(&hware, (char*)"True");
  set_object_color(&hware, (char*)"blue");
  set_object_type(&hware, (char*)"bulb");
  set_object_name(&hware, (char*)"test");
  set_object_dim(&hware, 10);
  hardware hware2 = *init_hardware(&hware);
  set_object_state(&hware2, (char*)"True");
  set_object_color(&hware2, (char*)"blue");
  set_object_type(&hware2, (char*)"bulb");
  set_object_name(&hware2, (char*)"aye");
  set_object_dim(&hware2, 10);
  DM tmpDM = *init_DM(&tmpDM);
  create_DM(&tmpDM, (char*)"127.0.0.1", (char*)"255.255.255.0");
  add_to_DM(&tmpDM, &hware);
  add_to_DM(&tmpDM, &hware2);
  hardware goodWare = get_hardware_name(&tmpDM, (char*)"test");
  hardware badWare = get_hardware_name(&tmpDM, (char*)"bad");
  ASSERT_STREQ(badWare.name, (char*)"NONE");
  ASSERT_STREQ(goodWare.name, (char*)"test");
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
