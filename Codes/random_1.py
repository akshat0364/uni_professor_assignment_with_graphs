import csv
import random

# Function to generate random CS and DS course preferences mixed
def generate_cs_ds_preferences(existing_courses):
    cs_ds_courses = ["CS F11", "CS F21", "CS F22", "CS F23", "CS F24", "CS F31", "CS F32", "CS F33", "CS F34","DS F21", "DS F22"]
    random.shuffle(cs_ds_courses)
    
    # Ensure uniqueness
    cs_ds_courses = [course for course in cs_ds_courses if course not in existing_courses]
    existing_courses.extend(cs_ds_courses)
    
    return ";".join(cs_ds_courses[:4]) + ";"

# Function to generate random HCS course preferences
def generate_hcs_preferences(existing_courses):
    hcs_courses = ["HCS F21", "HCS F22", "HCS F11", "HCS F12"]
    random.shuffle(hcs_courses)
    
    # Ensure uniqueness
    hcs_courses = [course for course in hcs_courses if course not in existing_courses]
    existing_courses.extend(hcs_courses)
    
    return ";".join(hcs_courses[:2]) + ";"

# Function to generate random UDEL course preferences
def generate_udel_preferences(existing_courses):
    udel_courses = ["UDEL F21", "UDEL F22", "UDEL F31", "UDEL F32", "UDEL F41", "UDEL F42"]
    random.shuffle(udel_courses)
    
    # Ensure uniqueness
    udel_courses = [course for course in udel_courses if course not in existing_courses]
    existing_courses.extend(udel_courses)
    
    return ";".join(udel_courses[:4]) + ";"

# Function to generate random HDEL course preferences
def generate_hdel_preferences(existing_courses):
    hdel_courses = ["HDEL F11", "HDEL F12", "HDEL F21", "HDEL F22"]
    random.shuffle(hdel_courses)
    
    # Ensure uniqueness
    hdel_courses = [course for course in hdel_courses if course not in existing_courses]
    existing_courses.extend(hdel_courses)
    
    return ";".join(hdel_courses[:2]) + ";"

def generate_data(professor_number, type_list):
    existing_courses = []

    # Ensure that all CDC courses are in the preferences
    cdc_courses = ["CS F11", "CS F21", "CS F22", "CS F23", "CS F24", "CS F31", "CS F32", "CS F33", "CS F34","DS F21", "DS F22"]
    random.shuffle(cdc_courses)
    
    ug_cdc_courses = generate_cs_ds_preferences(existing_courses)
    hd_cdc_courses = generate_hcs_preferences(existing_courses)
    ug_del_courses = generate_udel_preferences(existing_courses)
    hd_el_courses = generate_hdel_preferences(existing_courses)
    
    # Ensure constant counts of X1, X2, and X3
    x_type = random.choice(type_list)
    type_list.remove(x_type)
    data_type = f"{x_type}"

    return [f"PF-{professor_number}", ug_cdc_courses, hd_cdc_courses, ug_del_courses, hd_el_courses, data_type]

num_rows = 25

headers = ["Professor", "UG CDC", "HD CDC", "UG DEL", "HD EL", "TYPE"]

type_list = ['X1'] * 3 + ['X2'] * 15 + ['X3'] * 7

with open('random_data.csv', 'w', newline='') as csvfile:
    csv_writer = csv.writer(csvfile, delimiter=',')  
    
    # Write headers
    csv_writer.writerow(headers)

    # Generate and write data
    for professor_number in range(1, num_rows + 1):
        data_row = generate_data(professor_number, type_list)
        csv_writer.writerow(data_row)