import serial
import time
from tkinter import *

# Создаем окно приложения
window = Tk()
window.title("Добро пожаловать в приложение PythonRu")
window.geometry("600x400")

# Текстовые поля для отображения данных
label1 = Label(window, text="Значение с датчика 1:", font=("Arial", 18))
label1.pack(anchor='n', pady=5)

label2 = Label(window, text="Значение с датчика 2:", font=("Arial", 18))
label2.pack(anchor='n', pady=5)

label3 = Label(window, text="Значение с датчика 3:", font=("Arial", 18))
label3.pack(anchor='n', pady=5)
+
data_label = Label(window, text="Массив данных: [0.00, 0.00, 0.00]", font=("Arial", 18))
data_label.pack(anchor='center', pady=20)

# Настройки порта
port = 'COM4'  # Замените на ваш порт, например, '/dev/ttyUSB0' на Linux
baudrate = 9600
timeout = 1

# Открываем последовательный порт
ser = serial.Serial(port, baudrate, timeout=timeout)

# Даем время на установку соединения
time.sleep(2)


# Функция для обновления данных с последовательного порта
def update_data():
    if ser.in_waiting > 0:
        # Чтение данных с порта
        line = ser.readline().decode('utf-8').rstrip()
        # Разделение строки на значения для каждого датчика
        values = line.split(',')

        # Обновляем значения с датчиков
        if len(values) >= 3:
            label1.config(text=f"ТДС: {values[0]}")
            label2.config(text=f"Темпиратура: {values[1]}")
            label3.config(text=f"Эхолот: {values[2]}")
            data_label.config(text=f"Массив данных: {values}")

    # Перезапуск функции через 1 секунду
    window.after(1000, update_data)


# Запускаем цикл обновления данных
window.after(1000, update_data)

# Запуск основного цикла интерфейса
window.mainloop()

# Закрываем порт при завершении программы
ser.close()
