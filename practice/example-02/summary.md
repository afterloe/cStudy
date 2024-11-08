
数据格式
采用 CSV 文件存储所有词条数据，用 UTF-8 进行编码，用 Excel 的话，别直接打开，否则编码是错的。在 Excel 里选择数据，来自文本，然后设定逗号分割，UTF-8 编码即可。

字段	解释
word	单词名称
phonetic	音标，以英语英标为主
definition	单词释义（英文），每行一个释义
translation	单词释义（中文），每行一个释义
pos	词语位置，用 "/" 分割不同位置
collins	柯林斯星级
oxford	是否是牛津三千核心词汇
tag	字符串标签：zk/中考，gk/高考，cet4/四级 等等标签，空格分割
bnc	英国国家语料库词频顺序
frq	当代语料库词频顺序
exchange	时态复数等变换，使用 "/" 分割不同项目，见后面表格
detail	json 扩展信息，字典形式保存例句（待添加）
audio	读音音频 url （待添加）