import csv,os
fname = 'date.csv'

# Read last datetime saved in CSV file
# Year, Month, Day, Hour, Minute, Second
# Set the linux system time to that date
# Might need better error handling
# Designed to run on Arduino boot


def setDate(filename):
	try:
		with open(filename,'rb') as f:
			reader=csv.reader(f)
			for row in reader:
				lastDate = map(int, row)
				os.system('date -s %(year)04d.%(month)02d.%(day)02d-%(hour)02d:%(minute)02d:%(second)02d' % {"year":lastDate[0],"month":lastDate[1],"day":lastDate[2],"hour":lastDate[3],"minute":lastDate[4],"second":lastDate[5]})

	except IOError:
		print "Could not read file: ", filename



setDate(fname)


