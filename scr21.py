#!/usr/bin/python3
import os, re, sys
print("Введите имя файла. Для получения справки нажмите '?'.")
inp = input()
while (inp == '?'):
	print("Введите имя файла, копии которого необходимо удалить. ВНИМАНИЕ! Программа не принимает файлы с суффиксами '-', '~', ''\n",
			  "Формат ввода: абсюлютное имя файла (вида /home/user_name/folder_1/.../folder_n/file_name.suffix) либо относительное (./folder_1/.../folder_n/file_name.suffix), где './' - текущая директория.\n",
			  "Если файл расположени в текущей директории, допустимо его указание в формате prefix.suffix.")
	inp = input().lower
if (inp.find('.') == -1):
	print("Программа не принимает файлы с суффиксами '~', '-', ' '.") # в данном случае прекращаем выполнение программы
	sys.exit()

if (os.path.isfile(inp)):  # если введенный путь указывает на существующий файл
	file = inp
	suff = file[file.rfind('.'):].lower()  # находим суффикс файла (срез строки от последнего вхождения '.' до конца)
	print(f"Суффикс файла: {suff}")

	print(f"Найдены файлы, имеющие суффикс {suff}:")
	root = os.getenv("HOME") #узнаем домашнюю директорию; для windows: from os.path import expanduser; root = expanduser("~")
	tree = os.walk(root)
	files = []  # список всех файлов, удовлетворяющих условию задачи
	for dir in tree:  # в каждой поддиректории ищем файлы, которые имеют суффикс suff и добавляем в общий список
		files_in_dir = [os.path.join(dir[0], f) for f in dir[2] if (re.match(f'^.*{suff}$', f.lower())) ] #список подходящих файлов (абсолютный путь) в данной поддиректории
		files += files_in_dir

	files.remove(os.path.abspath(file)) # уберем из списка исходный файл, т.к. его удалять нельзя
	for f in files:
		print(f)

	print("Удаленные копии:")
	file_text = open(file, 'rb').read()
	for f in files:
		compare_text = open(f, 'rb').read()
		if file_text == compare_text: # поочередно открываем файлы из списка и сравниваем с исходным
			print(f)
			os.remove(f) # удаляем совпавшие с исходным файлы

else:
	print("Такого файла не существует.")
