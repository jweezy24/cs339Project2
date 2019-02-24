import unittest
import random
import lightObject
import outletObject
import utilsForDevs
import controlCenter
import lightGroup
import miscObject
import tempMain

class TestAPIMethods(unittest.TestCase):
    def setUp(self):
        self.light = lightObject.Bulb( "1", color="red", dim=0, switch=False)
        self.light2 = lightObject.Bulb( "2", color="red", dim=0, switch=False)
        self.light3 = lightObject.Bulb( "3", color="red", dim=0, switch=False)
        self.light4 = lightObject.Bulb( "4", color="red", dim=0, switch=False)
        self.outlet = outletObject.Outlet(2, False, "5")
        self.group = lightGroup.lightGroup("6", False)
        self.doorbell = miscObject.newSmartDev("7", "doorbell", "ring", False, False)
        self.hub = controlCenter.controller()
        self.parser = tempMain.Parser()

    def suite():
        #all back tests
        #tests = [
        #'test_flip_light',
        #'test_flip_outlet',
        #'test_flip_group',
        #'test_get_dim',
        #'test_set_dim',
        #'test_get_state_light',
        #'test_get_color',
        #'test_set_color',
        #'test_get_state_group',
        #'test_get_state_outlet',
        #'test_move_item',
        #'test_add_outlet',
        #'test_add_group',
        #'test_add_light_new',
        #'test_get_item_by_name_outlet',
        #'test_get_item_by_name_group',
        #'test_add_light_group',
        #'test_add_outlet_group',
        #'test_remove_item_group',
        #'test_check_open',
        #'test_plugin_light_outlet',
        #'test_update_light',
        #'test_update_group',
        #'test_update_outlet',
        #'test_get_object_by_name',
        #'test_delete'
        #]

        #all front tests
        tests = [
        'test_gather_group_f',
        'test_show_fixtures_f',
        'test_add_group_f',
        'test_add_light_f',
        'test_add_outlet_f',
        # 'test_give_help_f', # can't think of how to test this one, it's just some prints
        'test_exit_prompt_f',
        'test_name_conflict_f',
        'test_color_response_f',
        'test_integer_response_f',
        'test_yes_no_f',
        'test_parse_f',
        'test_r_f',
        ]

    # def test_r_f(self):
    #     thing = tempMain.r()
    #     self.assertIsNotNone(thing)

    def test_parse_f(self):
        result = self.parser.parse('not a legit command')
        self.assertIsNone(result)

    # def test_yes_no_f(self):
    #     #yes_no = self.parser.yes_no('it doesn\'t matter (y/n)')
    #     self.assertFalse(yes_no, 'yn')
    #
    # def test_integer_response_f(self):
    #     #integer = self.parser.integer_response()
    #     self.assertEqual(type(integer), type(45))
    #
    # def test_color_response_f(self):
    #     #color = self.parser.color_response()
    #     self.assertIn(color, self.parser.colors)

    def test_name_conflict_f(self):
        conflict = self.parser.name_conflict('')
        self.assertFalse(conflict)

    # def test_exit_prompt_f(self):
    #     #output = self.parser.exit_prompt()
    #     self.assertIsNone(output)

    # def test_add_outlet_f(self):
    #     output = self.parser.add_outlet()
    #     self.assertTrue(self.hub.fixtures > 0)
    #
    # def test_add_light_f(self):
    #     output = self.parser.add_light()
    #     self.assertTrue(self.hub.fixtures > 0)
    #
    # def test_add_group_f(self):
    #     output = self.parser.add_group()
    #     self.assertIsNone(output)

    def test_show_fixtures_f(self):
        expected_output = ['Name: 1\t Type: bulb\t State: on',
                           'Name: 3\t Type: outlet\t State: off', [], #empty list if from get_full_outlet_object, ours is empty rn
                           'Name: 10\t Type: group\t State: on\n\tName: 1\t Type: bulb\t State: off\n\tName: 2\t Type: bulb\t State: off']
        self.hub.add_light('1', 'pink', True)
        self.hub.add_outlet(2 , False, '3')
        members = (self.light, self.light2)
        self.hub.add_group("10", members, True)
        output = self.hub.show_fixtures()
        self.assertTrue(expected_output == output)


    # def test_gather_group_f(self):
    #     self.hub.add_light('1', 'pink', True)
    #     self.hub.add_light('2', 'pink', True)
    #     test_group = self.hub.gather_group()
    #     self.assertTrue(test_group[0].switch)
    #     self.assertTrue(test_group[1].switch)

    def test_flip_light(self):
        self.light.flip()
        self.assertTrue(self.light.switch)

    def test_flip_outlet(self):
        self.outlet.flip()
        self.assertTrue(self.outlet.switch)

    def test_flip_group(self):
        self.group.flip()
        self.assertTrue(self.group.switch)

    def test_get_dim(self):
        self.assertEqual(self.light.getDim(), 0)

    def test_set_dim(self):
        self.light.setDim(10)
        self.assertEqual(self.light.getDim(), 10)

    def test_get_color(self):
        self.assertEqual(self.light.getColor(), "red")

    def test_set_color(self):
        self.light.setColor("blue")
        self.assertEqual(self.light.getColor(), "blue")

    def test_get_state_light(self):
        self.assertEqual(self.light2.getState(), "Light is off")

    def test_get_state_outlet(self):
        self.assertFalse(self.outlet.getState())

    def test_get_state_group(self):
        self.assertEqual(self.group.getState(), [("6","off")])

    #adding a light to a controller
    def test_add_light_new(self):
        self.hub.add_light("8", "blue", True)
        self.assertEqual(self.hub.get_object_by_name("8").type, "bulb")

    def test_add_light_group_existing(self):
        self.group.addItem(self.light)
        self.assertEqual(self.group.getItemByName("1").type, "bulb")

    def test_add_light_group_new(self):
        self.group.addItem(lightObject.Bulb("7", "blue", False))
        self.assertEqual(self.group.getItemByName("7").type, "bulb")

    def test_add_group(self):
        members = (self.light, self.light2)
        members2 = (self.light3, self.light4)
        self.hub.add_group("10", members, True)
        self.hub.add_group("11", members2, False)
        self.assertTrue(self.hub.get_object_by_name("10").switch)
        self.assertFalse(self.hub.get_object_by_name("11").switch)

    def test_move_item(self):
        members = (self.light, self.light2)
        members2 = (self.light3, self.light4)
        self.hub.add_group("10", members, True)
        self.hub.add_group("11", members2, False)
        self.hub.move_item( "2", "11")
        self.assertEqual(self.hub.get_object_by_name("11").getItemByName("2").name, "2")

    def test_delete(self):
        self.hub.add_light("8", "blue", True)
        self.assertTrue(self.hub.get_object_by_name("8").name, "8")
        self.hub.delete("8")
        self.assertEqual(self.hub.get_object_by_name("8"), 'none')

    def test_check_open(self):
        self.assertEqual(self.outlet.checkOpen(), 2)
        self.outlet.plugInLight(self.light)
        self.assertEqual(self.outlet.checkOpen(), 1)

    def test_get_object_by_name(self):
        self.assertEqual(self.hub.get_object_by_name("1"),'none')
        self.hub.add_light("1", "red", False)
        self.assertEqual(self.hub.get_object_by_name("1").name, "1")

    def test_get_object_by_name_outlet(self):
        self.assertEqual(self.outlet.getItemByName("1"), 'none')
        self.outlet.plugInLight(self.light)
        self.assertEqual(self.outlet.getItemByName("1").name, "1")

    def test_remove_item_group(self):
        self.group.addItem(self.light)
        self.assertEqual(self.group.getItemByName("1").type, "bulb")
        self.group.removeItem("1")
        self.assertEqual(self.group.getItemByName("1"), 'none')

    def test_plugin_light_outlet(self):
        self.assertEqual(self.outlet.checkOpen(), 2)
        self.outlet.plugInLight(self.light)
        self.assertEqual(self.outlet.checkOpen(), 1)
        self.assertEqual(self.outlet.getItemByName("1").name, "1")

    def test_get_item_by_name_group(self):
        self.group.addItem(self.light)
        self.assertEqual(self.group.getItemByName("1").type, "bulb")

    def test_add_outlet(self):
        self.hub.add_outlet(2,False,"3")
        self.assertEqual(self.hub.get_object_by_name("3").name, "3")

    def test_add_outlet_group(self):
        self.group.addItem(self.outlet)
        self.assertEqual(self.group.getItemByName("5").name, "5")

    def test_misc_get_event(self):
        self.assertEqual(self.doorbell.getEvent(), "ring")

    def test_misc_get_state(self):
        self.assertFalse(self.doorbell.getState())

    def test_misc_can_be_plugged(self):
        self.assertFalse(self.doorbell.can_be_plugged())

    def test_misc_flip(self):
        self.assertFalse(self.doorbell.getState())
        self.doorbell.flip()
        self.assertTrue(self.doorbell.getState())

    def test_misc_trigger_event(self):
        self.assertEqual(self.doorbell.triggerEvent(), "ring")




unittest.main()
