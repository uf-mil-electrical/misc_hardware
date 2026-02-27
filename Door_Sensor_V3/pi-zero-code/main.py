

# Dependencies
import qwiic_vl53l1x
import requests
import time

# HTTP Request setup (communication w/ Discord bot)
URL = "http://10.138.173.121:5001/"
HEADERS = {
	"Content-Type": "application/json",
	"X-Github-Event": "door_toggled",
}

# Initialize ToF sensor
ToF = qwiic_vl53l1x.QwiicVL53L1X()
ToF.sensor_init()

# Settings
tof_read_delay = 0.005		# delay time in seconds
countdown_length = 10		# countdown duration in seconds
open_door_distance = 100	# how close the door must be to be "open"

# Variables for operation
lab_state = None
last_door_state = None
countdown_active = False
timer_start = None


# HTTP POST function
def post_lab_state(lab_state: str) -> None:
	
	payload = {"door_status": "open" if lab_state == "OPEN" else "closed"}
	
	try:
		r = requests.post(URL, headers=HEADERS, json=payload, timeout=5)
		print(f"POST {URL} -> {r.status_code} {r.text}")
	
	except requests.RequestException as e:
		print(f"HTTP error: {e}")


# Run main program
while True:
	try:
		
		# Read distance from ToF
		ToF.start_ranging()
		time.sleep(tof_read_delay)
		distance = ToF.get_distance()
		ToF.stop_ranging()
		
		# Determine door state
		if distance <= open_door_distance:
			door_state = "OPEN"
		else:
			door_state = "CLOSED"
			
		# Debug print statement
		#print(f"Distance = {distance}, Door = {door_state}, countdown_active = {countdown_active}")
		
		# Check if the door's state has changed
		if door_state != last_door_state:
			print(f"Door state changed to {door_state}, starting countdown")
			countdown_active = True
			timer_start = time.time()
			last_door_state = door_state
			
		# If countdown is active...
		if countdown_active:
			
			# check elapsed time
			elapsed = time.time() - timer_start
			
			# if door state changes again during countdown
			if door_state != last_door_state:
				print("Countdown cancelled")
				countdown_active = False
				
			# if countdown finishes and door hasn't changed state again
			elif elapsed >= countdown_length:
				lab_state = door_state
				countdown_active = False
				post_lab_state(lab_state)
				print(f"Countdown complete! - lab state changed to {lab_state}")
				
		time.sleep(0.1)
		
	except Exception as e:
		print(e)
