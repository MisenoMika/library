# 修改编译选项，建议使用 -Wall 代替 -w 以显示警告信息
CC = g++
CCFLAG = -g -Wall  # 将 -w 改为 -Wall

# 在依赖项中添加 StudentVector.o，确保依赖关系正确
proj6: main.o World.o Weather.o Decision.o Student.o Group.o StudentVector.o
	$(CC) $(CCFLAG) -o proj6 main.o World.o Weather.o \
	StudentVector.o Decision.o Student.o Group.o

main.o: main.C World.h
	$(CC) $(CCFLAG) -c -o main.o main.C

World.o: World.C World.h Group.h
	$(CC) $(CCFLAG) -c -o World.o World.C

Weather.o: Weather.C Weather.h
	$(CC) $(CCFLAG) -c -o Weather.o Weather.C

# 补充缺失的 StudentVector.o 编译规则
StudentVector.o: StudentVector.C StudentVector.h
	$(CC) $(CCFLAG) -c -o StudentVector.o StudentVector.C

Decision.o: Decision.C Decision.h
	$(CC) $(CCFLAG) -c -o Decision.o Decision.C

Student.o: Student.C Student.h Decision.h
	$(CC) $(CCFLAG) -c -o Student.o Student.C

Group.o: Group.C Group.h Student.h
	$(CC) $(CCFLAG) -c -o Group.o Group.C

# 声明 clean 为伪目标，避免与同名文件冲突
.PHONY: clean
clean:
	rm -rf proj6 *.o
