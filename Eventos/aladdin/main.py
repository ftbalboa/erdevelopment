#!/usr/bin/env python
# 
#


##IMPORTS 
import random, sys, csv
import time
import RPi.GPIO as GPIO
import os
import sys 
from subprocess import Popen
import subprocess

##VIDEO Y GPIO
GPIO.setmode(GPIO.BOARD)

GPIO.setup(16, GPIO.OUT)
GPIO.setup(18, GPIO.OUT)
GPIO.setup(21, GPIO.IN, pull_up_down=GPIO.PUD_UP)	##BOTON
GPIO.setup(22, GPIO.IN, pull_up_down=GPIO.PUD_UP)	##OPTO
GPIO.setup(23, GPIO.IN, pull_up_down=GPIO.PUD_UP) ##PUENTE
GPIO.setup(24, GPIO.IN, pull_up_down=GPIO.PUD_UP) ##KILLVIDEO

TRAILER = ("/home/pi/Videos/LADY ACTIS SECUENCIA 1.mp4")
JUEGUEN = ("/home/pi/Videos/LADY ACTIS SECUENCIA 2.mp4")
PERDIO = ("/home/pi/Videos/LADY ACTIS SECUENCIA 3.mp4")
REMERA = ("/home/pi/Videos/LADY ACTIS SECUENCIA 4.mp4")
POSTER = ("/home/pi/Videos/LADY ACTIS SECUENCIA 4.mp4")
ENTRADA = ("/home/pi/Videos/LADY ACTIS SECUENCIA 4.mp4")

##CONSTANTS GLOBALS
PROBA_REM	= 1380
PROBA_ENT	= 1724
PROBA_POS	= 6896

PERSONASXDIA = 1000

DIA_INICIAL = 6
DIA_FINAL	  = 12	
STOCK_MAX	  = 1450 

STOCK_POSTERS_START = 2000
DIA_STOCK_POSTERS = 7

##Globales
proba_win = 2071
stock_remeras = 0
stock_posters = 0
stock_entradas = 0
dia_actual = 0
stock_total = [dia_actual,stock_remeras,stock_posters,stock_entradas]
trailer = False

def screen_off():
        os.system("xscreensaver-command -activate")
        time.sleep(1)

def screen_on():
        time.sleep(1)
        os.system("xscreensaver-command -deactivate")

def leeStock():
	with open('hola.csv', newline='') as File: 
		nuevo_stock = [0,0,0,0]
		n_objetos = 0
		reader = csv.reader(File)
		for row in reader:
			nuevo_stock[n_objetos] = row
			n_objetos += 1
		return nuevo_stock
		
def cargaStock(total, objeto):
	if objeto is 'dia':
		aux = 0
		while aux < len(total):
			if total[aux][0] == 'dia':
				return  total[aux][1]
			aux += 1
	
	if objeto is 'remeras':
		aux = 0
		while aux < len(total):
			if total[aux][0] == 'remeras':
				return  total[aux][1]
			aux += 1
	
	if objeto is 'posters':
		aux = 0
		while aux < len(total):
			if total[aux][0] == 'posters':
				return  total[aux][1]
			aux += 1
	if objeto is 'entradas':
		aux = 0
		while aux < len(total):
			if total[aux][0] == 'entradas':
				return  total[aux][1]
			aux += 1
			
	print ('objeto no listado')
	return 'error'

def updateStock ():
	
	global stock_entradas,stock_posters,stock_remeras,dia_actual
	
	with open('hola.csv', 'w', newline='') as File:
		writer = csv.writer(File, delimiter=',', quotechar='"', quoting=csv.QUOTE_NONE)

		writer.writerows(	[['dia', dia_actual],
					['entradas', stock_entradas],
					['posters', stock_posters],
					['remeras', stock_remeras]])
	
def juega():
	global PERDIO, JUEGUEN
	bolero = random.randint(0, 9999)
	if bolero >= proba_win:
		screen_off()
		os.system('killall omxplayer.bin')
          omxc = Popen(['omxplayer', '-b', '--no-osd' , PERDIO])
          screen_on()
          time.sleep(10)
 		screen_off()
		os.system('killall omxplayer.bin')
          omxc = Popen(['omxplayer', '-b','--loop', '--no-osd' , JUEGUEN])
          screen_on()         
		return False
	else:
		return True

def quePremio():
	global PROBA_ENT,PROBA_POS,PROBA_REM,stock_entradas,stock_posters,stock_remeras,stock_total,REMERA,POSTER,JUEGUEN,ENTRADA
	while(True):
		bolero = random.randint(0, 9999)
		if bolero < PROBA_REM and stock_remeras > 0:
		screen_off()
		os.system('killall omxplayer.bin')
          omxc = Popen(['omxplayer', '-b', '--no-osd' , REMERA])
          screen_on()
          time.sleep(10)
 		screen_off()
		os.system('killall omxplayer.bin')
          omxc = Popen(['omxplayer', '-b','--loop', '--no-osd' , JUEGUEN])
          screen_on()
			return 'remera'
		if bolero < PROBA_REM + PROBA_POS and bolero > PROBA_REM and stock_posters > 0 :
		screen_off()
		os.system('killall omxplayer.bin')
          omxc = Popen(['omxplayer', '-b', '--no-osd' , POSTER])
          screen_on()
          time.sleep(10)
 		screen_off()
		os.system('killall omxplayer.bin')
          omxc = Popen(['omxplayer', '-b','--loop', '--no-osd' , JUEGUEN])
          screen_on()
			return 'poster'
		if bolero < PROBA_REM + PROBA_POS + PROBA_ENT and bolero > PROBA_REM + PROBA_POS and bolero > PROBA_REM and stock_entradas > 0:
		screen_off()
		os.system('killall omxplayer.bin')
          omxc = Popen(['omxplayer', '-b', '--no-osd' , ENTRADA])
          screen_on()
          time.sleep(10)
 		screen_off()
		os.system('killall omxplayer.bin')
          omxc = Popen(['omxplayer', '-b','--loop', '--no-osd' , JUEGUEN])
          screen_on()
			return 'entrada'

GPIO.output(16,True)
GPIO.output(18,True)

omxc = Popen(['omxplayer', '-b', '--loop', '--no-osd' , TRAILER])

stock_total = leeStock()
stock_entradas = int(cargaStock(stock_total,'entradas'))
stock_remeras = int(cargaStock(stock_total,'remeras'))
stock_posters = int(cargaStock(stock_total,'posters'))
dia_actual  = int(cargaStock(stock_total,'dia'))


dia_actual = int(time.strftime("%d"))

if dia_actual == DIA_STOCK_POSTERS and stock_posters = 0
	stock_posters = STOCK_POSTERS_START

proba_win = (stock_entradas + stock_remeras + stock_posters)*10000/((DIA_FINAL-dia_actual+1)*PERSONASXDIA)

updateStock()   

while(True):

	if trailer:
          if not (GPIO.input(22)):
               trailer = False
			time.sleep(1)
			screen_off()
			os.system('killall omxplayer.bin')
			omxc = Popen(['omxplayer', '-b','--loop', '--no-osd' , JUEGUEN])
			screen_on()      
	else:
		if not (GPIO.input(21)):
			if juega():
				Premio = quePremio()
				if Premio == 'remera':
					stock_remeras -= 1
				if Premio == 'poster':
					stock_posters -= 1
				if Premio == 'entrada': 
					stock_entradas -= 1
				if(GPIO.input(23)):
					updateStock()
		if not (GPIO.input(22)):
               trailer = True
			time.sleep(1)
			screen_off()
			os.system('killall omxplayer.bin')
			omxc = Popen(['omxplayer', '-b','--loop', '--no-osd' , JUEGUEN])
			screen_on()
			
	if not (GPIO.input(24)):
		os.system('killall omxplayer.bin')	
			      
	print('entradas',stock_entradas)
	print('posters',stock_posters)
	print('remeras',stock_remeras)
	print('dia',dia_actual)



