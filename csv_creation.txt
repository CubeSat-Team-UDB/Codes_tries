import serial
import csv
import time
import os
from datetime import datetime

# CONFIGURA AQUÍ tu puerto serie:
PORT = "/dev/ttyUSB0"  # En Windows puede ser "COM3"
BAUDRATE = 115200

csv_file = "telemetria_lora.csv"

def main():
    # Mostrar ruta absoluta del archivo CSV
    print("CSV se guardará en:", os.path.abspath(csv_file))

    # Abrir puerto serie
    ser = serial.Serial(PORT, BAUDRATE, timeout=1)
    time.sleep(2)  # Esperar a que se estabilice la conexión

    print("Escuchando datos LoRa...")

    with open(csv_file, mode='a', newline='') as file:
        writer = csv.writer(file)

        # Escribir cabeceras si el archivo está vacío
        if file.tell() == 0:
            writer.writerow(["timestamp", "lat", "lon", "presion", "temp"])

        while True:
            try:
                line = ser.readline().decode('utf-8').strip()
                if line and ',' in line:
                    fields = line.split(",")
                    if len(fields) == 4:
                        now = datetime.now().isoformat()
                        writer.writerow([now] + fields)
                        print(f"[LOG] Guardado: {fields}")
                    else:
                        print(f"[WARN] Paquete incompleto: {line}")
            except KeyboardInterrupt:
                print("Terminando...")
                break
            except Exception as e:
                print(f"[ERROR] {e}")

    ser.close()

if __name__ == "__main__":
    main()
