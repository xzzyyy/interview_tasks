На вход консольному приложению дается путь к каталогу с файлами и имя файла с результатами. В каждом файле - первая строка - данные, остальные строки задают набор разделителей в формате одна строка - один разделитель. Строки-разделители могут содержать пробелы и любые другие символы кроме переноса строки.


Нужно разбить первую строку на подстроки, по всем разделителям из своего файла одновременно - т. е. результирующие подстроки не должны содержать ни одного разделителя. Парсинг файлов должен работать параллельно несколько потоков,
а полученные подстроки должны быть помещены в один выходной файл. Реализация должна быть полностью на STL/Boost и демонстрировать понимание ООП, работу с потоками и объектами синхронизации.


Исключить использование голых указателей, заменяя их на стандартные контейнеры и Smart Pointers. Важно чтобы код был читаем и в целом оформлен на коммерческом уровне. Приветствуется использование стандартных алгоритмов/лямбд (имеющихся в STL/Boost).


### Входные данные.

Первая строка входного файла – строка для разбора. Каждая последующая строка содержит один разделитель.

### Выходные данные.

Информация по каждому файлу идет последовательно не пересекаясь с информацией с других файлов. При этом не важно в каком порядке выводятся эти файлы с информацией в выходном файле.


### Пример

    [Имя файла hd.txt]:
    Подстрока 1 файла 1
    Подстрока 2 файла 1
    Подстрока…
    Подстрока n файла 1
    [Имя файла ab.txt]:
    Подстрока 1 файла 2
    Подстрока 2 файла 2
    Подстрока…
    Подстрока m файла 2
