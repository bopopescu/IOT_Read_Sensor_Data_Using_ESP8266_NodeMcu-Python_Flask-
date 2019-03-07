from flask import Flask, render_template, request
import mysql.connector
app = Flask(__name__)

#mysql database 
#create database python_db;
#create table records(id int auto_increment, primary key(id),
#  distance varchar(30), weight varchar(30), timing timestamp default current_timestamp); 

db=mysql.connector.connect(host="localhost",user="root",password="root",database="python_db")
cursor=db.cursor()

	
@app.route('/',methods = ['GET'])
def result():
	if request.args.get('device')=='esp':
		sensor=request.args.get('sensor')
		distance=request.args.get('distance')
		weight=request.args.get('weight')
		sql = "INSERT INTO RECORDS (distance, weight) VALUES ('{0}','{1}')".format(distance,weight)
		cursor.execute(sql)
		db.commit()
		return render_template('sensor_details.html',sensor=sensor)

	elif request.args.get('details') =='view':
		start=request.args.get('start')
		end=request.args.get('end')
		start=start+" 00-00-01"
		end=end+" 23-59-59"
		print(start)
		print(end)
		sql = "select * from records where timing>='{0}' and timing<='{1}'".format(start,end)
		cursor.execute(sql)
		filter_data=cursor.fetchall()
		return render_template('sensor_details.html', home=filter_data, success="success")
	
	else:
		return render_template('sensor_details.html')


if __name__ == '__main__':
   app.run(debug = True)

# 192.168.43.183

#change ip: python -m flask run --host=192.168.43.183


	
