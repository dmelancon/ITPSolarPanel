import csv
from datetime import datetime

# Writes current system datetime to CSV file every minute
# Year, Month, Day, Hour, Minute, Second
# Running once per minute on cron, check "crontab -l" to confirm

def writeDate():
	fname = '/mnt/sda1/date.csv'
	date = datetime.now()
	today = [date.year,date.month,date.day,date.hour,date.minute,date.second]
	with open(fname,'wb') as f:
		writer = csv.writer(f)
		writer.writerow(today)
		print "Current date & time is : ", today




writeDate()


