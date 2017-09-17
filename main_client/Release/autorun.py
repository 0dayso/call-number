import __main__
import rpc
cln=rpc.RpcClient('127.0.0.1',8900)

def get_title():
    fun=__main__.exe_fun__['list_add_column']
    for n,x in enumerate(cln.get_title()):
        fun(n,*x)
    return 0

def new_number():
    nm,_id,pn,tp=__main__.stack__[:4]
    tp=tp[0].upper()
    cln.new_number(nm,_id,pn,tp)
    return 0

def refresh():
    pcs=cln.refresh()
    __main__.exe_fun__['clear_list']()
    fun_set=__main__.exe_fun__['list_set_item']
    for r,pc in enumerate(pcs):
        for c,itm in enumerate(pc):
            fun_set(r,c,itm)

def print_number():
    __main__.msgbox('print number.')
