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

svr.run(1)
