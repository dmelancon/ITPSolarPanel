import csv,threading
from datetime import datetime

# Writes current system datetime to CSV file every minute
# Year, Month, Day, Hour, Minute, Second
# Uses threading timer, will execute every 60 seconds

def writeDate():
	fname = '/mnt/sda1/date.csv'
	date = datetime.now()
	today = [date.year,date.month,date.day,date.hour,date.minute,date.second]
	with open(fname,'wb') as f:
		writer = csv.writer(f)
		writer.writerow(today)
		print "Current date & time is : ", today

	threading.Timer(60.0,writeDate).start()




writeDate()


