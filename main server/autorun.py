import time
import json
import os
cwd=os.getcwd()

#disable stdeff
class CErr(object):
	def __init__(self):
		pass
	def write(self,s):
		pass
import sys
sys.stderr=CErr()

print('取号服务正在运行中...')

#server data
#piece format:
#[No,win,name,id,phone,type,status,start,stop,comment]
g_pieces=[]
g_cnt=1


#rpc service
import rpc
svr=rpc.RpcSvr('0.0.0.0',8900)

def get_title():
	ret=[]
	try:
		with open('title.dat',encoding='utf-8') as f:
			for l in f:
				a,b=l.split(' ')
				ret.append((a,int(b)))
	except Exception as exp:
		pass#return str(exp)
	return ret
svr.reg_fun(get_title)

def new_number(nm,_id,pn,tp):
	global g_pieces,g_cnt
	piece=[str(g_cnt),'',nm,_id,pn,tp,'已取号','','','']
	print(piece)
	g_pieces.append(piece)
	g_cnt+=1
	return 0
svr.reg_fun(new_number)

def refresh():
	return g_pieces
svr.reg_fun(refresh)

svr.run(1)
