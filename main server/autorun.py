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
g_pieces=[]
g_cnt=1


#rpc service
import rpc
svr=rpc.RpcSvr('0.0.0.0',8900)


def save_data():
	with open('serialize.dat','w') as f:
		json.dump((g_pieces,g_cnt),f)

def load_data():
	global g_pieces,g_cnt
	try:
		with open('serialize.dat','r') as f:
			g_pieces,g_cnt=json.load(f)
	except:
		pass

def init_new_day():
	global g_pieces,g_cnt
	g_cnt=1
	with open('history.dat','a') as f:
		for pc in g_pieces:
			f.write(json.dumps(pc)+'\n')
	g_pieces=[]
	return 1
svr.reg_fun(init_new_day)

def get_title():
	ret=[('号码',40), ('窗口',40), ('姓名',60),
	 	('身份证',150), ('电话',100), ('类型',40),
	 	('状态',60), ('开始时间',150),
	 	('结束时间',150), ('备注',150)]
	return ret
svr.reg_fun(get_title)

def new_number(nm,_id,pn,tp):
	global g_pieces,g_cnt
	piece=[str(g_cnt),'',nm,_id,pn,tp,'已取号','','','']
	g_pieces.append(piece)
	g_cnt+=1
	save_data()
	return 0
svr.reg_fun(new_number)

def refresh():
	return g_pieces
svr.reg_fun(refresh)

load_data()
svr.run(1)
