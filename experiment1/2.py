'''
Author       : czq
Date         : 2021-03-16 14:24:28
LastEditors  : czq
LastEditTime : 2021-03-30 14:59:22
'''

import jieba

s = '你好，很高兴遇见你。'
cut = jieba.cut(s)
print(' '.join(cut))
