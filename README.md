# OOP-LABS №1

# Вариант №3

Напишите функцию, которая принимает строку круглых скобок и определяет, является ли порядок
скобок правильным. Функция должна возвращать true, если строка допустима, и false, если
недопустима.

Примеры:

"()" => true

")(()))" => false

"(" => false

"(())((()())())" => true

Ограничения: 
0 <= длина ввода <= 100

Все входные данные будут строками, состоящими только из символов ( и ). Пустые строки считаются сбалансированными (и, следовательно, валидными) и будут проверяться.