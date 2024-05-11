# -*- coding: utf-8 -*- 


from flask import Flask,render_template,request,g,session,url_for,send_file
import MySQLdb
import os
import json
from flask_cors import CORS
from time import localtime, strftime  
import datetime
import uuid
import pandas as pd


#MySQL配置
host = 'localhost'
user = 'root'
password = '123'
database = 'pro'



app = Flask(__name__) 



cors = CORS(app, resources={r"/*": {"origins": "*"}}) 



    
    
@app.route("/addt",methods=['POST','GET'])
def addt():
    db = MySQLdb.connect(host=host, user=user, passwd=password, db=database)
    cursor = db.cursor()
    
    temp = request.values.get("temp")
    humi = request.values.get("humi")
    time = strftime("%H:%M:%S", localtime()) 
    dates = str(datetime.date.today())
    
    cursor.execute("insert into tmp(date,time,temp,humi) values(%s,%s,%s,%s)",(dates,time,temp,humi))
    
    db.commit()
    
    return "200"
    
    
@app.route("/gett",methods=['POST','GET'])
def gett():
    db = MySQLdb.connect(host=host, user=user, passwd=password, db=database)
    cursor = db.cursor()
    
    dates = str(datetime.date.today())
    
    
    cursor.execute("SELECT temp,time FROM(SELECT temp,time FROM tmp WHERE date = %s ORDER BY time DESC LIMIT 10)aa ORDER BY time",(dates,))

    
    
    data = cursor.fetchall()
	
	
	
    return json.dumps(data)
    
    
    

    
    

    
		
	
    
if __name__ == '__main__':  
    app.run(host='0.0.0.0',port=5000,debug=True)