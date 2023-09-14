# Домашние задания

Лектор: П.Н. Советов\
Семинарист: В.С. Степанюк

## ДЗ №1. Эмулятор командной строки

Разработать эмулятор командной строки vshell.
В качестве аргумента vshell принимает образ файловой системы известного формата (tar, zip).

Обратите внимание: программа должна запускаться прямо из командной строки, а файл с виртуальной файловой системой не нужно распаковывать у пользователя.
В vshell должны поддерживаться команды pwd, ls, cd и cat.

Необходимо поддержать ключ командной строки `--script имя_файла` для загрузки списка выполняемых команд из файла.
Кроме того, в коде должна присутствовать функция тестирования всех реализованных команд.

Ваша задача сделать работу vshell как можно более похожей на сеанс bash в Linux.
Реализовать vshell можно на Python или других ЯП, но кроссплатформенным образом.

## ДЗ №2. Визуализатор зависимостей пакета

Написать на выбранном вами языке программирования программу, которая принимает в качестве аргумента командной строки имя пакета, а возвращает граф его зависимостей в виде текста на языке Graphviz. На выбор: для npm или для pip. Пользоваться самими этими менеджерами пакетов запрещено. Главное, чтобы программа работала даже с неустановленными пакетами и без использования pip/npm.

## ДЗ №3. Конфигурационный язык на основе S-выражений

Реализовать синтаксический разбор придуманного вами конфигурационного языка, основанного на S-выражениях (в которых у нас есть только скобки, пробелы и значения различных типов) для представления информации о студентах и группах (см. задачу 1 из практики 3).

1. Формат должен быть основан на грамматике, приведенной ниже. Детали формата на основе S-выражений необходимо продумать самостоятельно и обязательно описать их в БНФ. Формат должен поддерживать комментарии, типы данных: число, имя, строка.
2. Разбор реализовать средствами типа Lex/Yacc на выбранном ЯП (SLY в Python, Flex/Bison в C/C++, ANTLR в Java, ...).
3. После разбора результат преобразовать в JSON-представление. Пример из ПР 3.1 у вас должен получиться на выходе таким же и это надо показать в решении.
4. Программа должна иметь интерфейс командной строки: входным аргументом является имя конфигурационного файла, а результатом выполнения является вывод на экран (stdout) результата трансляции в JSON.

Дополнительный плюс за поддержку принципа DRY (то есть в язык можно добавить переменные, функции и так далее).

Базовая грамматика, которую необходимо реализовать и расширить для своих нужд (комментарии, представление data...):

```
<program> ::= <s-exp-list> 
<s-exp> ::= <data> |  '(' <s-exp-list> ')'
<s-exp-list> ::= <sexp> <s-exp-list> |
```

Конфликты shift/reduce, которые выдает Yacc-подобный инструмент, недопустимы. Они возникают, если у вас неоднозначная грамматика, то есть одному предложению языка могут соответствовать несколько вариантов разбора. В этом случае нужно поправить грамматику.

Полезные ссылки:

S-выражения https://ru.wikipedia.org/wiki/S-%D0%B2%D1%8B%D1%80%D0%B0%D0%B6%D0%B5%D0%BD%D0%B8%D0%B5
https://matt.might.net/articles/parsing-s-expressions-scala/

Генераторы синтаксических анализаторов
SLY (Python): https://sly.readthedocs.io/en/latest/sly.html

ANTLR (Java): https://ru.wikipedia.org/wiki/ANTLR

Lex/Yacc (C/C++): http://rus-linux.net/lib.php?name=/MyLDP/algol/lex-yacc-howto.html

## ДЗ №4. Мини-версия Make

Реализовать свою мини-версию Make.

Для описания задач, зависимостей и команд можно использовать язык реализации (если это скриптовый язык в духе Питона) или же реализовать собственный язык с помощью средств из ДЗ 3. Если у вас нет хороших идей на этот счет, то используем синтаксис make, но позволяем отступы делать "по-человечески", а не только с помощью "\t".

Для определения порядка выполнения задач должен использоваться алгоритм топологической сортировки. Уже выполненные задачи повторно не выполняются.

Для определения изменений в зависимостях задач (файлах и других видах данных) необходимо использовать не время изменения файла, а хеш-значения, см. https://medium.com/@buckaroo.pm/build-systems-should-use-hashes-over-timestamps-54d09f6f2c4

Обратите внимание, вам нужно хешировать содержимое файлов. То есть для хранения аналога файловой системы с информацией о файлах вполне можно использовать тот же JSON-объект, а вот хешировать сами данные лучше чем-нибудь проверенным, с малой вероятностью коллизий. Посмотрите стандартную библиотеку. Для Питона это https://docs.python.org/3/library/hashlib.html

Проверить работоспособность реализованной системы автоматизации сборки на примере civgraph (том варианте, где создаются файлы!), а также на собственном примере компиляции приложения.

Иными словами, идеальное решение подразумевает настоящую, пусть и примитивную, систему сборки, которая работала бы с реальными файлами и произвольными командами, а также включала в себя БД в каком-то виде для хранения состояния между запусками.

## ДЗ №5. Визуализатор коммитов для git
Описание  Разработать CLI-утилиту для выдачи информации по локальному git-репозиторию. Назначение утилиты – визуализатор графа изменений дерева (tree: файлы и папки) проекта с выводом в формате dot (graphviz).

Данные извлекаются из папки .git без использования сторонних программ и библиотек. То есть нельзя из программы вызывать команды git для получения данных (например "git log" и "git cat-file"). Но можно и нужно пользоваться сведениями отсюда: https://git-scm.com/book/ru/v2/Git-%D0%B8%D0%B7%D0%BD%D1%83%D1%82%D1%80%D0%B8-%D0%9E%D0%B1%D1%8A%D0%B5%D0%BA%D1%82%D1%8B-Git

Обязательно приведите примеры работы вашей утилиты.

## ДЗ №6. Программное управление QEMU

Реализовать выполнение программ студентов, написанных на C/C++, в "песочнице", организованной с помощью QEMU и образа Linux.

Цель – не позволить некорректной или вредоносной программе сломать всю систему. Подобные "песочницы" используются, к примеру, у исследователей из антивирусных компаний, которые анализируют новые вредоносные программы.

Решение должно работать в Windows и Linux.

Размер всех данных для "песочницы" не должен превышать 512 Мб (не включая сам QEMU).

Необходимо продумать способ автоматически загружать новые исходные тексты в виртуальный Linux, а после завершения работы проверяемой программы – получать данные в хост-систему.
