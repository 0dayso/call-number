import winsound
import time
import threading
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
print('客户通知服务正在运行...')
#voice service
voice_queue=[]#append (uid,winid) to this queue,to play notify sound.
def sound_routine():
	while True:
		if not voice_queue:
			time.sleep(0.3)
			continue
		uid,winid=voice_queue.pop(0)
		s='%03d'%(uid)
		winsound.PlaySound(cwd+'\\wav\\q.wav',winsound.SND_FILENAME)
		for c in s:
			winsound.PlaySound(cwd+'\\wav\\'+c+'.wav',winsound.SND_FILENAME)
		winsound.PlaySound(cwd+'\\wav\\ck%d.wav'%(winid),winsound.SND_FILENAME)

thd=threading.Thread(target=sound_routine)
thd.start()

#screen show service.
import office
ppt=office.PowerPoint(1)
pre=ppt.open(cwd+'\\1.pptx')
sli=pre.slides[0]
shps=sli.shapes
for sp in shps:
	sp.text=''
pre.run()

#rpc service
import rpc
svr=rpc.RpcSvr('0.0.0.0',8800)

txt_queue=['']*len(shps)
def add_notice(uid,winid):
	global txt_queue
	s='请%03d号客户到%d号窗口办理业务'%(uid,winid)
	if s in txt_queue:
		voice_queue.append((uid,winid))
		return 1
	txt_queue=[s]+txt_queue
	txt_queue.pop()
	for n in range(len(shps)):
		shps[n].text=txt_queue[n]
	voice_queue.append((uid,winid))
	return 1
svr.reg_fun(add_notice)

svr.run(1)
