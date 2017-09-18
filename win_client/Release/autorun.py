import __main__
import rpc
import json

g_ip=''
g_win_no=''
g_types=''
cln=rpc.RpcClient(g_ip,8900)

def load():
	global g_ip,g_win_no,g_types,cln
	try:
		with open('setting.json','r') as f:
			g_ip,g_win_no,g_types=json.load(f)
		cln=rpc.RpcClient(g_ip,8900)
	except:
		pass

def save():
	global g_ip,g_win_no,g_types,cln
	g_ip,g_win_no,g_types=__main__.stack__[:3]
	cln=rpc.RpcClient(g_ip,8900)
	with open('setting.json','w') as f:
		json.dump((g_ip,g_win_no,g_types),f)

load()

def call_number():
	_no,nm,_id,phn=cln.call_number(g_win_no,g_types)
	if not _no:
		return '没有找到能在本窗口办理业务的群众。'
	ret='号码：%s\r\n姓名：%s\r\n身份证：%s\r\n电话：%s'%(_no,nm,_id,phn)
	return ret

def task_complete():
	cmnt=__main__.stack__[0]
	ok=__main__.stack__[1]
	ret=cln.task_complete(g_win_no,cmnt,ok)
	if ret:
		return '已提交！'
	else:
		return '提交失败。'