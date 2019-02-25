import unittest
import sys
sys.path.insert(0, '../../src/local')
import deviceManager

class TestDMMethods(unittest.TestCase):
    def setUp(self):
        self.Dm = deviceManager.deviceManager()
        self.json_str_1 = """{'dim': 0, 'name': 'stan',
        'color': 'white', 'ip': '192.168.1.2', 'switch': False, 'port': 44860,
        'op': 'heartbeat'}"""
        self.json_str_2 = '{"op":"list"}'
        self.json_str_3 = '{"op":"turn-on", "port":44860}'

    def test_json_parser_heartbeat(self):
        self.Dm.parse_json(self.json_str_1)
        self.assertTrue(self.Dm.objects[0][1]["name"] == "stan")

    def test_json_parser_list(self):
        self.Dm.parse_json(self.json_str_1)
        retVal = self.Dm.parse_json(self.json_str_2)
        self.assertTrue(retVal == "Port: 44860\tOn: False\n")

    def test_json_parser_turn_on(self):
        self.Dm.parse_json(self.json_str_1)
        self.Dm.turn_on(44860, True)
        self.assertTrue(self.Dm.objects[0][1]["switch"])

    def test_get_object(self):
        self.Dm.parse_json(self.json_str_1)
        self.assertTrue(self.Dm.get_object(44860))
    def test_remove_Item(self):
        self.Dm.parse_json(self.json_str_1)
        self.assertFalse(self.Dm.remove_Item(44860))        

unittest.main()
