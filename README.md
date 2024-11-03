# 中山大学软件工程学院初级实训第二次项目
## 公司人员和薪酬管理系统

## 操作说明：
### 进入系统，加载employees.txt中的员工数据
![alt text](<屏幕截图 2024-11-03 100356.png>)

### 输入0 - 5选择操作
#### 1 => 输入所有员工数据，同时抹除原有员工数据（需要事先确认）
##### 输入员工名字即可，若无新的员工，则输入“@”即可
![alt text](<屏幕截图 2024-11-03 100440.png>)
#### 2 => 增加新员工数据
##### 输入员工姓名以及等级，同时有error处理机制，若等级为不合理数字，则抛出错误
![alt text](<屏幕截图 2024-11-03 100559.png>)
#### 3 => 删除员工数据（根据ID删除）
##### 输入要删除员工的ID，若不存在该员工，抛出error信息
![alt text](<屏幕截图 2024-11-03 100533.png>)
#### 4 => 输入工作时间和销售额
##### 输入Technician的工作时长，以及SalesMan和SalesManager的销售额，若输入信息为不合理字符，则抛出错误，要求重新输入或跳过
![alt text](<屏幕截图 2024-11-03 100521.png>)
#### 5 => 展示所有员工的薪酬（以表格形式）
##### 以ID顺序展示员工薪酬，同时列出对应等级,若有员工未输入sales或workhour，则对是否展示进行确认
![alt text](<屏幕截图 2024-11-03 100450.png>)
#### 0 => 退出系统
##### 系统输出“goodbye”表示退出，同时将员工数据存入employees.txt
![alt text](<屏幕截图 2024-11-03 100636.png>)

## 创新
### 使用不同颜色的文字进行操作提醒，如操作1的抹除原有员工数据的确认操作使用红色文字，更加醒目
### 加入了错误输入检测，保证系统的稳定性
### 加入了loading动画，个人认为给乏味的系统带去了一丝小趣味

## 改进
### 个人认为代码量过多，可以通过提取函数进行代码量的缩减
### 可以分多文件进行类的编写
### 部分函数的功能可以更加单一而集中，力求一个函数解决一个问题（便于日后新功能添加）