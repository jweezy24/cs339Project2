import light_bulb
import argparse

if __name__ == '__main__':
	parser = argparse.ArgumentParser()
	parser.add_argument('-n', '--name', required=True, type=str,
						help='the name you would like for the light you are starting up.')
	args = parser.parse_args()
    b = lightObject.Bulb(name=args.name)
    b.listen()