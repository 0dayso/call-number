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

def time_now():
	return time.strftime('%Y.%m.%d %H:%M:%S')
#server data
g_pieces=[]
g_cnt=1
g_sessions=dict()

#main client service
import rpc
svr=rpc.RpcSvr('0.0.0.0',8900)


def save_data():
	with open('serialize.dat','w') as f:
		json.dump((g_pieces,g_cnt,g_sessions),f)

def load_data():
	global g_pieces,g_cnt,g_sessions
	try:
		with open('serialize.dat','r') as f:
			g_pieces,g_cnt,g_sessions=json.load(f)
	except:
		pass

def init_new_day():
	global g_pieces,g_cnt,g_sessions
	g_cnt=1
	with open('history.dat','a') as f:
		for pc in g_pieces:
			f.write(json.dumps(pc)+'\n')
	g_pieces=[]
	g_sessions=dict()
	save_data()
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

#win client service
def call_number(win_no,types):
	global g_pieces
	if win_no in g_sessions:
		return g_sessions[win_no]
	types=types.upper()
	for pc in g_pieces:
		if pc[1]=='' and pc[5] in types:
			pc[1]=win_no
			pc[6]='办理中'
			pc[7]=time_now()
			ret=pc[0],pc[2],pc[3],pc[4]
			g_sessions[win_no]=ret
			save_data()
			return ret
	return ['','','','']
svr.reg_fun(call_number)

def task_complete(win_no,comment,ok):
	if win_no not in g_sessions:
		return 0
	_no=g_sessions[win_no][0]
	for pc in g_pieces:
		if pc[0]==_no:
			pc[6]='成功' if ok else '失败'
			pc[8]=time_now()
			pc[9]=comment
			g_sessions.pop(win_no)
			save_data()
			return 1
	return 0

svr.reg_fun(task_complete)

load_data()
svr.run(1)
