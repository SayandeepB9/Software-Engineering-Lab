#importing libraries    
import pickle
import tkinter as tk
from tkinter import messagebox
import tkinter.font as tkfont
import os
import re

#class for Person with attributes
class Person:
    def __init__(self, username, password, first_name, last_name,\
                  email, phone, birthday, address, city, country, postal_code):
        self.username = username
        self.password = password
        self.first_name = first_name
        self.last_name = last_name
        self.email = email
        self.phone = phone
        self.birthday = birthday
        self.address = address
        self.city = city
        self.country = country
        self.postal_code = postal_code
        self.attempts = 3

#class for Teacher with attributes
class Teacher(Person):
    def __init__(self, username, password, first_name, last_name,\
                email, phone, birthday, address, city, country, postal_code,\
                teacher_id, courses_taught=[]):
        super().__init__(username, password, first_name, last_name,\
                  email, phone, birthday, address, city, country, postal_code)
        self.type = "Teacher"
        self.teacher_id = teacher_id
        self.courses_taught = courses_taught

#class for Student with attributes
class Student(Person):
    def __init__(self, username, password, first_name, last_name,\
                email, phone, birthday, address, city, country, postal_code,\
                student_id, cgpa, courses_taken=[], societies=[]):
        super().__init__(username, password, first_name, last_name,\
                  email, phone, birthday, address, city, country, postal_code)
        self.student_id = student_id
        self.cgpa = cgpa
        self.courses_taken = courses_taken
        self.societies = societies

#class for UG Student with attributes
class UG_Stud(Student):
    def __init__(self, username, password, first_name, last_name,\
                email, phone, birthday, address, city, country, postal_code,\
                student_id, cgpa, year_of_study, degree_programme,\
                courses_taken=[], societies=[]):
        super().__init__(username, password, first_name, last_name,\
                email, phone, birthday, address, city, country, postal_code,\
                student_id, cgpa, courses_taken, societies)
        self.type = "UG Student"
        self.year_of_study = year_of_study
        self.degree_programme = degree_programme

#class for PG Student with attributes
class PG_Stud(Student):
    def __init__(self, username, password, first_name, last_name,\
                email, phone, birthday, address, city, country, postal_code,\
                student_id, cgpa, year_of_study, degree_programme,\
                TA_for_courses=[], courses_taken=[], societies=[]):
        super().__init__(username, password, first_name, last_name,\
                email, phone, birthday, address, city, country, postal_code,\
                student_id, cgpa, courses_taken, societies)
        self.type = "PG Student"
        self.year_of_study = year_of_study
        self.degree_programme = degree_programme
        self.TA_for_courses = TA_for_courses


#class for entities. It contains all the functionalities of the system
#ENTITIES is a list of all the entities in the system
class Entities():
    def __init__(self):
        pass

    #function to add an entity to the system
    def add_entity(self, entity):
        ENTITIES.append(entity)

    #function to get an entity from the system by username
    def get_entity(self, username):
        for entity in ENTITIES:
            if entity.username == username:
                return entity
        print("Entity not found")
        return None
    
    #function to match password of an entity
    #if password matches, attempts is reset to 3
    #if password does not match, attempts is decremented by 1
    #if attempts becomes 0, the entity is deactivated by the system
    def match_password(self, username, password):
        for entity in ENTITIES:
            if entity.username == username:
                if entity.password == password:
                    entity.attempts = 3
                    return True
                else:
                    messagebox.showinfo("Error", "Invalid password")
                    entity.attempts -= 1
                    if entity.attempts == 0:
                        self.delete_entity(username)
                        messagebox.showinfo("Error", "Account deleted due to too many failed attempts")
                    return False
        messagebox.showinfo("Error", "Invalid username")
        return False
    
    #function to delete an entity from the system
    def delete_entity(self, username):
        for entity in ENTITIES:
            if entity.username == username:
                ENTITIES.remove(entity)
                return True
        return False
    
    #function to update an entity in the system
    def update_entity(self, username, new_entity):
        for i, entity in enumerate(ENTITIES):
            if entity.username == username:
                ENTITIES[i] = new_entity
                print(f"Entity {new_entity.username} updated")
                messagebox.showinfo("Success", "Entity updated")
                return True
        return False
    
    #function to create an entity based on type
    def create_entity(self, type, username, password, first_name, last_name,\
                email, phone, birthday, address, city, country, postal_code,\
                teacher_id, courses_taught=[], student_id=None, cgpa=None, year_of_study=None,\
                degree_programme=None, courses_taken=[], societies=[],\
                TA_for_courses=[]):
        if type == "Teacher":
            entity = Teacher(username, password, first_name, last_name,\
                email, phone, birthday, address, city, country, postal_code,\
                teacher_id, courses_taught)
            return entity

        elif type == "UG Student":
            entity = UG_Stud(username, password, first_name, last_name,\
                email, phone, birthday, address, city, country, postal_code,\
                student_id, cgpa, year_of_study, degree_programme,\
                courses_taken, societies)
            return entity
        
        elif type == "PG Student":
            entity = PG_Stud(username, password, first_name, last_name,\
                email, phone, birthday, address, city, country, postal_code,\
                student_id, cgpa, year_of_study, degree_programme,\
                TA_for_courses, courses_taken, societies)
            return entity
    
#the main driving class for the gui interface
class LayoutApp(tk.Tk):
    def __init__(self, *args, **kwargs):
        tk.Tk.__init__(self, *args, **kwargs)
        self.title_font = tkfont.Font(family='Helvetica', size=20, weight="bold", slant="italic")
        self.medium_font = tkfont.Font(family='Helvetica', size=15, weight="bold", slant="italic")
        self.small_font = tkfont.Font(family='Helvetica', size=10, weight="bold", slant="italic")
        self.geometry("800x600")  # Set the initial size of the window
        self.mode = tk.StringVar()
        self.current_entity = None

        # Create a container to hold all the frames for the subsequent pages
        # Frame upper and lower are for the title and footer for all pages
        Frame_upper = tk.Frame(self, bg="blue", height=50)
        Frame_upper.pack(side="top", fill="both")
        container = tk.Frame(self)
        container.pack(side="top", fill="both", expand=True)
        Frame_lower = tk.Frame(self, bg="grey", height=50)
        Frame_lower.pack(side="bottom", fill="both")
        Frame_upper.grid_rowconfigure(0, weight=1)
        Frame_upper.grid_columnconfigure(0, weight=1)
        container.grid_rowconfigure(0, weight=1)
        container.grid_columnconfigure(0, weight=1)
        Frame_lower.grid_rowconfigure(0, weight=1)
        Frame_lower.grid_columnconfigure(0, weight=1)
        self.container = container

        #label of ERP IIT KHARAUGPUR
        label1 = tk.Label(Frame_upper, text="ERP IIT KHARAGPUR", font=self.title_font, bg="lightgreen", fg="indigo")
        label1.pack(side="top", pady=10)

        label2 = tk.Label(Frame_lower, text="©SB_2024", font=self.small_font, bg="fuchsia", fg="lavender")
        label2.pack(side="bottom", pady=10)

        self.frames = {}
        self.show_frame("StartPage")

    #function to show a frame in the container
    def show_frame(self, page_name):
        '''Show a frame for the given page name'''
        if page_name not in self.frames:
            F = globals()[page_name]
            frame = F(parent=self.container, controller=self)
            self.frames[page_name] = frame
            frame.grid(row=0, column=0, sticky="nsew")
        else:
            frame = self.frames[page_name]
            frame.destroy()  # Destroy the existing frame instance
            F = globals()[page_name]
            frame = F(parent=self.container, controller=self)
            self.frames[page_name] = frame
            frame.grid(row=0, column=0, sticky="nsew")
        frame.tkraise()

#this is the first page of the gui
class StartPage(tk.Frame):
    def __init__(self, parent, controller):
        tk.Frame.__init__(self, parent)
        #set background colour to alice blue
        self.configure(bg="alice blue")
        self.grid_rowconfigure(0, weight=1)
        self.grid_columnconfigure(0, weight=1)
        self.controller = controller

        Frame_upper = tk.Frame(self, bg="lawngreen", height=50)
        Frame_upper.pack(side="top", fill="both")
        Frame_middle = tk.Frame(self, bg="aquamarine", height=300)
        Frame_middle.pack(side="top", fill="both", expand=True)
        # Frame_lower = tk.Frame(self, bg="black", height=50)
        # Frame_lower.pack(side="bottom", fill="both")
        Frame_upper.grid_rowconfigure(0, weight=1)
        Frame_upper.grid_columnconfigure(0, weight=1)
        Frame_middle.grid_rowconfigure(0, weight=1)
        # Frame_lower.grid_rowconfigure(0, weight=1)
        # Frame_lower.grid_columnconfigure(0, weight=1)
        
        #welcome label
        label2 = tk.Label(Frame_upper, text="Welcome to the ERP System", font=controller.title_font, bg="pink", fg="black")
        label2.pack(side="top", pady=10)

        #label new user
        label2 = tk.Label(Frame_middle, text="New User?", font=controller.medium_font, bg="indigo", fg="lavender")
        label2.pack(side="top", pady=(50,10))

        #button for registration
        button1 = tk.Button(Frame_middle, text="Register", font=controller.title_font, command=lambda: controller.show_frame("RegistrationPage"), bg="green", fg="lavender")
        button1.pack(side="top", pady=(5,30))

        #label for existing user
        label3 = tk.Label(Frame_middle, text="Existing User?", font=controller.medium_font, bg="indigo", fg="lavender")
        label3.pack(side="top", pady=10)

        #button for sign in
        button2 = tk.Button(Frame_middle, text="Sign In", font=controller.title_font, command=lambda: controller.show_frame("SignInPage"), bg="green", fg="lavender")
        button2.pack(side="top", pady=10)

        #button for exit
        button3 = tk.Button(Frame_middle, height=1, text="Exit", font=controller.title_font, command=self.exit, bg="red", fg="lavender", activebackground="maroon")
        button3.pack(side="top", pady=10)

    #function to exit the gui
    def exit(self):
        self.controller.destroy()

#this is the registration page of the gui
class RegistrationPage(tk.Frame):
    def __init__(self, parent, controller):
        tk.Frame.__init__(self, parent)
        self.controller = controller
        self.entities = Entities()
        self.configure(bg="alice blue")
        self.grid_rowconfigure(0, weight=1)
        self.grid_columnconfigure(0, weight=1)
   
        Frame_upper = tk.Frame(self, bg="lawngreen", height=50)
        Frame_upper.pack(side="top", fill="both")
        Frame_middle = tk.Frame(self, bg="aquamarine", height=400)
        Frame_middle.pack(side="top", fill="both", expand=True)
        Frame_lower = tk.Frame(self, bg="orchid", height=50)
        Frame_lower.pack(side="bottom", fill="both")
        Frame_upper.grid_rowconfigure(0, weight=1)
        # Frame_middle.grid_rowconfigure(0, weight=1)
        Frame_lower.grid_rowconfigure(0, weight=1)

        #label for registration
        label1 = tk.Label(Frame_upper, text="Registration", width=20, font=controller.title_font, bg="lightcoral", fg="black")
        label1.pack(side="top", pady=10)

        #drop down menu for user type
        controller.mode = tk.StringVar()
        controller.mode.set("Teacher")
        choices = ["Teacher", "UG Student", "PG Student"]
        drop_down = tk.OptionMenu(Frame_middle, controller.mode, *choices)
        menu = drop_down.nametowidget(drop_down.menuname)
        menu.config(font=controller.medium_font, bg="lightblue", fg="indigo", activebackground="lightseagreen", activeforeground="indigo")
        drop_down.config(bg="lightgreen", fg="indigo", font=controller.small_font, width=10, activebackground="lightseagreen")
        drop_down.grid(row=1, column=2, padx=10, pady=10)

        self.username = tk.StringVar()
        self.password = tk.StringVar()
        self.confirm_password = tk.StringVar()
        self.first_name = tk.StringVar()
        self.last_name = tk.StringVar()
        self.email = tk.StringVar()
        self.phone = tk.StringVar()
        
        #create labels and entry boxes for user details
        label_username = tk.Label(Frame_middle, text="Username")
        label_username.config(bg="lightblue", fg="indigo", font=controller.medium_font)
        label_password = tk.Label(Frame_middle, text="Password")
        label_password.config(bg="lightblue", fg="indigo", font=controller.medium_font)
        label_confirm_password = tk.Label(Frame_middle, text="Confirm Password")
        label_confirm_password.config(bg="lightblue", fg="indigo", font=controller.medium_font)
        label_first_name = tk.Label(Frame_middle, text="First Name")
        label_first_name.config(bg="lightblue", fg="indigo", font=controller.medium_font)
        label_last_name = tk.Label(Frame_middle, text="Last Name")
        label_last_name.config(bg="lightblue", fg="indigo", font=controller.medium_font)
        label_email = tk.Label(Frame_middle, text="Email")
        label_email.config(bg="lightblue", fg="indigo", font=controller.medium_font)
        label_phone = tk.Label(Frame_middle, text="Phone")
        label_phone.config(bg="lightblue", fg="indigo", font=controller.medium_font)

        label_username.grid(row=2, column=1, padx=10, pady=10, sticky="w")
        label_password.grid(row=3, column=1, padx=10, pady=10, sticky="w")
        label_confirm_password.grid(row=4, column=1, padx=10, pady=10, sticky="w")
        label_first_name.grid(row=5, column=1, padx=10, pady=10, sticky="w")
        label_last_name.grid(row=6, column=1, padx=10, pady=10, sticky="w")
        label_email.grid(row=7, column=1, padx=10, pady=10, sticky="w")
        label_phone.grid(row=8, column=1, padx=10, pady=10, sticky="w")

        entry_username = tk.Entry(Frame_middle, textvariable=self.username, width=40)
        entry_username.config(bg="lightgreen", fg="indigo", font=controller.small_font)
        entry_password = tk.Entry(Frame_middle, textvariable=self.password, show="*", width=40)
        entry_password.config(bg="lightgreen", fg="indigo", font=controller.small_font)
        entry_confirm_password = tk.Entry(Frame_middle, textvariable=self.confirm_password, show="*", width=40)
        entry_confirm_password.config(bg="lightgreen", fg="indigo", font=controller.small_font)
        entry_first_name = tk.Entry(Frame_middle, textvariable=self.first_name, width=40)
        entry_first_name.config(bg="lightgreen", fg="indigo", font=controller.small_font)
        entry_last_name = tk.Entry(Frame_middle, textvariable=self.last_name, width=40)
        entry_last_name.config(bg="lightgreen", fg="indigo", font=controller.small_font)
        entry_email = tk.Entry(Frame_middle, textvariable=self.email, width=40)
        entry_email.config(bg="lightgreen", fg="indigo", font=controller.small_font)
        entry_phone = tk.Entry(Frame_middle, textvariable=self.phone, width=40)
        entry_phone.config(bg="lightgreen", fg="indigo", font=controller.small_font)
        
        entry_username.grid(row=2, column=2, padx=10, pady=10, sticky="w")
        entry_password.grid(row=3, column=2, padx=10, pady=10, sticky="w")
        entry_confirm_password.grid(row=4, column=2, padx=10, pady=10, sticky="w")
        entry_first_name.grid(row=5, column=2, padx=10, pady=10, sticky="w")
        entry_last_name.grid(row=6, column=2, padx=10, pady=10, sticky="w")
        entry_email.grid(row=7, column=2, padx=10, pady=10, sticky="w")
        entry_phone.grid(row=8, column=2, padx=10, pady=10, sticky="w")

        #create buttons for register, reset and back
        button_register = tk.Button(Frame_lower, text="Register", width=10, command=self.register, bg="green", fg="white")
        button_reset = tk.Button(Frame_lower, text="Reset", width=10, command=self.reset, bg="yellow", fg="black")
        button_back = tk.Button(Frame_lower, text="Back", width=10, command=lambda: controller.show_frame("StartPage"), bg="red", fg="white")
        button_exit = tk.Button(Frame_lower, text="Exit", width=10, command=self.controller.destroy, bg="maroon", fg="white")
        button_register.pack(side="left", padx=10, pady=10)
        button_reset.pack(side="left", padx=10, pady=10)
        button_back.pack(side="left", padx=10, pady=10)
        button_exit.pack(side="left", padx=10, pady=10)

    #function to register an entity after checking all the conditions
    def register(self):
        #username must be unique
        if self.entities.get_entity(self.username.get()) != None:
            print("Username already exists")
            messagebox.showinfo("Error", "Username already exists")
            return
        
        #password must be 8-12 characters long
        #password must contain at least one uppercase letter, one lowercase letter, one digit and one special character
        if len(self.password.get()) < 8 or len(self.password.get()) > 12:
            print("Password must be 8-12 characters long")
            messagebox.showinfo("Error", "Password must be 8-12 characters long")
            return
        if not any(char.isupper() for char in self.password.get()):
            print("Password must contain at least one uppercase letter")
            messagebox.showinfo("Error", "Password must contain at least one uppercase letter")
            return
        if not any(char.islower() for char in self.password.get()):
            print("Password must contain at least one lowercase letter")
            messagebox.showinfo("Error", "Password must contain at least one lowercase letter")
            return
        if not any(char.isdigit() for char in self.password.get()):
            print("Password must contain at least one digit")
            messagebox.showinfo("Error", "Password must contain at least one digit")
            return
        if not any(not char.isalnum() for char in self.password.get()):
            print("Password must contain at least one special character")
            messagebox.showinfo("Error", "Password must contain at least one special character")
            return
        
        #first name, last name, email and phone must not be empty
        if self.first_name.get() == "":
            print("First name cannot be empty")
            messagebox.showinfo("Error", "First name cannot be empty")
            return
        if self.last_name.get() == "":
            print("Last name cannot be empty")
            messagebox.showinfo("Error", "Last name cannot be empty")
            return
        if self.email.get() == "":
            print("Email cannot be empty")
            messagebox.showinfo("Error", "Email cannot be empty")
            return
        if self.phone.get() == "":
            print("Phone cannot be empty")
            messagebox.showinfo("Error", "Phone cannot be empty")
            return
        
        #email and phone must be valid
        pattern = r'^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$'
        if not re.match(pattern, self.email.get()):
            print("Invalid email")
            messagebox.showinfo("Error", "Invalid email")
            return
        if not self.phone.get().isdigit():
            print("Invalid phone")
            messagebox.showinfo("Error", "Invalid phone")
            return
        
        if self.password.get() == self.confirm_password.get():
            entity = self.entities.create_entity(self.controller.mode.get(), self.username.get(), self.password.get(), self.first_name.get(), self.last_name.get(),\
                self.email.get(), self.phone.get(), birthday="", address="", city="", country="", postal_code="",\
                teacher_id="", courses_taught=[], student_id="", cgpa="", year_of_study="",\
                degree_programme="", courses_taken=[], societies=[],\
                TA_for_courses=[])
            self.entities.add_entity(entity)
            self.controller.current_entity = entity
            self.controller.show_frame("UserPage")
            self.reset()
            # self.controller.show_frame("StartPage")
        else:
            print("Passwords do not match")
            messagebox.showinfo("Error", "Passwords do not match")

    #function to reset the entry boxes
    def reset(self):
        self.username.set("")
        self.password.set("")
        self.confirm_password.set("")
        self.first_name.set("")
        self.last_name.set("")
        self.email.set("")
        self.phone.set("")

#this is the sign in page of the gui  
class SignInPage(tk.Frame):
    def __init__(self, parent, controller):
        tk.Frame.__init__(self, parent)
        self.controller = controller
        self.entities = Entities()
        self.configure(bg="alice blue")
        self.grid_rowconfigure(0, weight=1)
        self.grid_columnconfigure(0, weight=1)

        Frame_upper = tk.Frame(self, bg="lawngreen", height=50)
        Frame_upper.pack(side="top", fill="both")
        Frame_middle = tk.Frame(self, bg="aquamarine", height=400)
        Frame_middle.pack(side="top", fill="both", expand=True)
        Frame_lower = tk.Frame(self, bg="orchid", height=50)
        Frame_lower.pack(side="bottom", fill="both")
        Frame_upper.grid_rowconfigure(0, weight=1)
        # Frame_middle.grid_rowconfigure(0, weight=1)
        Frame_lower.grid_rowconfigure(0, weight=1)

        #label for sign in
        label1 = tk.Label(Frame_upper, text="Sign In", width=20, font=controller.title_font, bg="lightcoral", fg="black")
        label1.pack(side="top", pady=10)

        self.username = tk.StringVar()
        self.password = tk.StringVar()

        #create labels and entry boxes for user details
        label_username = tk.Label(Frame_middle, text="Username")
        label_username.config(bg="lightblue", fg="indigo", font=controller.medium_font)
        label_password = tk.Label(Frame_middle, text="Password")
        label_password.config(bg="lightblue", fg="indigo", font=controller.medium_font)

        label_username.grid(row=2, column=1, padx=10, pady=10, sticky="w")
        label_password.grid(row=3, column=1, padx=10, pady=10, sticky="w")

        entry_username = tk.Entry(Frame_middle, textvariable=self.username, width=40)
        entry_username.config(bg="lightgreen", fg="indigo", font=controller.small_font)
        entry_password = tk.Entry(Frame_middle, textvariable=self.password, show="*", width=40)
        entry_password.config(bg="lightgreen", fg="indigo", font=controller.small_font)

        entry_username.grid(row=2, column=2, padx=10, pady=10, sticky="w")
        entry_password.grid(row=3, column=2, padx=10, pady=10, sticky="w")

        #create buttons for sign in
        button_sign_in = tk.Button(Frame_middle, text="Sign In", width=10, command=self.sign_in, bg="green", fg="white")
        button_sign_in.grid(row=4, column=2, padx=10, pady=10, sticky="w")

        #create buttons for back and exit
        button_back = tk.Button(Frame_lower, text="Back", width=10, command=lambda: controller.show_frame("StartPage"), bg="red", fg="white")
        button_exit = tk.Button(Frame_lower, text="Exit", width=10, command=self.controller.destroy, bg="maroon", fg="white")
        button_back.pack(side="left", padx=10, pady=10)
        button_exit.pack(side="left", padx=10, pady=10)

    #function to sign in an entity
    def sign_in(self):
        if self.entities.match_password(self.username.get(), self.password.get()):
            self.controller.current_entity = self.entities.get_entity(self.username.get())
            self.reset()
            self.controller.show_frame("UserPage")
        else:
            return
        
    #function to reset the entry boxes
    def reset(self):
        self.username.set("")
        self.password.set("")

#this is the user page of the gui
class UserPage(tk.Frame):
    def __init__(self, parent, controller):
        tk.Frame.__init__(self, parent)
        self.controller = controller
        self.entities = Entities()
        
        Frame_upper = tk.Frame(self, bg="lawngreen", height=50)
        Frame_upper.pack(side="top", fill="both")
        Frame_middle = tk.Frame(self, bg="aquamarine", height=400)
        Frame_middle.pack(side="top", fill="both", expand=True)
        Frame_lower = tk.Frame(self, bg="orchid", height=50)
        Frame_lower.pack(side="bottom", fill="both")
        Frame_upper.grid_rowconfigure(0, weight=1)
        Frame_middle.grid_rowconfigure(0, weight=1)
        Frame_middle.grid_columnconfigure(0, weight=1)
        Frame_lower.grid_rowconfigure(0, weight=1)

        #if no user is signed in, show error message
        if self.controller.current_entity == None:
            label1 = tk.Label(Frame_middle, text="No user found", font=controller.medium_font, bg="lightblue", fg="indigo")
            label1.pack(side="top", pady=10)
            return
        
        #label for user page
        label1 = tk.Label(Frame_upper, text="User Page - "+controller.current_entity.type, width=30, font=controller.title_font, bg="lightcoral", fg="black")
        label1.pack(side="top", pady=10)

        # Create a Text widget with a vertical scrollbar
        text_widget = tk.Text(Frame_middle, wrap=tk.WORD, width=100, height=15, bg="moccasin", fg="darkblue", font=controller.medium_font)

        text_widget.pack(side="top", pady=10)

        scrollbar = tk.Scrollbar(Frame_middle, command=text_widget.yview)
        scrollbar.pack(side="right", fill="y")
        text_widget.config(yscrollcommand=scrollbar.set)

        # Add user details to the Text widget
        text_widget.insert(tk.END, "Username: \t" + self.controller.current_entity.username + "\n")
        text_widget.insert(tk.END, "First Name: \t" + self.controller.current_entity.first_name + "\n")
        text_widget.insert(tk.END, "Last Name: \t" + self.controller.current_entity.last_name + "\n")
        text_widget.insert(tk.END, "Email: \t" + self.controller.current_entity.email + "\n")
        text_widget.insert(tk.END, "Phone: \t" + self.controller.current_entity.phone + "\n")
        text_widget.insert(tk.END, "Birthday: \t" + self.controller.current_entity.birthday + "\n")
        text_widget.insert(tk.END, "Address: \t" + self.controller.current_entity.address + "\n")
        text_widget.insert(tk.END, "City: \t" + self.controller.current_entity.city + "\n")
        text_widget.insert(tk.END, "Country: \t" + self.controller.current_entity.country + "\n")
        text_widget.insert(tk.END, "Postal Code: \t" + self.controller.current_entity.postal_code + "\n")

        if controller.current_entity.type == "Teacher":
            text_widget.insert(tk.END, "Teacher ID: \t" + self.controller.current_entity.teacher_id + "\n")
            text_widget.insert(tk.END, "Courses Taught: \t" + str(self.controller.current_entity.courses_taught) + "\n")
        elif controller.current_entity.type == "UG Student":
            text_widget.insert(tk.END, "Student ID: \t" + self.controller.current_entity.student_id + "\n")
            text_widget.insert(tk.END, "Year of Study: \t" + str(self.controller.current_entity.year_of_study) + "\n")
            text_widget.insert(tk.END, "CGPA: \t" + str(self.controller.current_entity.cgpa) + "\n")
            text_widget.insert(tk.END, "Degree Programme: \t" + self.controller.current_entity.degree_programme + "\n")
            text_widget.insert(tk.END, "Courses Taken: \t" + str(self.controller.current_entity.courses_taken) + "\n")
            text_widget.insert(tk.END, "Societies: \t" + str(self.controller.current_entity.societies) + "\n")
        elif controller.current_entity.type == "PG Student":
            text_widget.insert(tk.END, "Student ID: \t" + self.controller.current_entity.student_id + "\n")
            text_widget.insert(tk.END, "Year of Study: \t" + str(self.controller.current_entity.year_of_study) + "\n")
            text_widget.insert(tk.END, "CGPA: \t" + str(self.controller.current_entity.cgpa) + "\n")
            text_widget.insert(tk.END, "Degree Programme: \t" + self.controller.current_entity.degree_programme + "\n")
            text_widget.insert(tk.END, "TA for Courses: \t" + str(self.controller.current_entity.TA_for_courses) + "\n")
            text_widget.insert(tk.END, "Courses Taken: \t" + str(self.controller.current_entity.courses_taken) + "\n")
            text_widget.insert(tk.END, "Societies: \t" + str(self.controller.current_entity.societies) + "\n")

        #create buttons for edit, delete, back and exit
        button_edit = tk.Button(Frame_lower, text="Edit", width=10, command=lambda: controller.show_frame("EditPage"), bg="green", fg="white")
        button_delete = tk.Button(Frame_lower, text="Deregister", width=10, command=self.delete, bg="red", fg="white")
        button_back = tk.Button(Frame_lower, text="Sign Out", width=10, command=lambda: controller.show_frame("StartPage"), bg="red", fg="white")
        button_exit = tk.Button(Frame_lower, text="Exit", width=10, command=self.controller.destroy, bg="maroon", fg="white")
        button_edit.pack(side="left", padx=10, pady=10)
        button_delete.pack(side="left", padx=10, pady=10)
        button_back.pack(side="left", padx=10, pady=10)
        button_exit.pack(side="left", padx=10, pady=10)

    #function to delete an entity
    def delete(self):
        #confirmation message box
        if messagebox.askyesno("Confirmation", "Are you sure you want to deregister your account?"):
            self.entities.delete_entity(self.controller.current_entity.username)
            self.reset()
            self.controller.show_frame("StartPage")
        else:
            return
        
    # self.controller.show_frame("StartPage")
    def reset(self):
        self.controller.current_entity = None

#this is the edit page of the gui
class EditPage(tk.Frame):
    def __init__(self, parent, controller):
        tk.Frame.__init__(self, parent)
        self.controller = controller
        self.entities = Entities()
        
        Frame_upper = tk.Frame(self, bg="lawngreen", height=50)
        Frame_upper.pack(side="top", fill="both")
        # Frame_middle = tk.Frame(self, bg="aquamarine", height=400)
        # Frame_middle.pack(side="top", fill="both", expand=True)
        Frame_lower = tk.Frame(self, bg="orchid", height=50)
        Frame_lower.pack(side="bottom", fill="both")
        Frame_upper.grid_rowconfigure(0, weight=1)
        # Frame_middle.grid_rowconfigure(0, weight=1)
        # Frame_middle.grid_columnconfigure(0, weight=1)
        Frame_lower.grid_rowconfigure(0, weight=1)

        # Create a canvas to hold the labels and entry widgets with a scrollbar
        canvas = tk.Canvas(self)
        scrollbar = tk.Scrollbar(self, orient="vertical", command=canvas.yview)
        scrollbar.pack(side="right", fill="y")
        canvas.pack(side="left", fill="both", expand=True)
        canvas.configure(yscrollcommand=scrollbar.set)

        # Create a window inside the canvas to hold the labels and entry widgets
        Frame_middle = tk.Frame(canvas)
        Frame_middle.config(bg="aquamarine", height=400)
        canvas.create_window((0, 0), window=Frame_middle)

        # Function to update the scroll region
        def on_frame_configure(event):
            canvas.configure(scrollregion=canvas.bbox("all"))

        # Bind the configure event of the frame to the update function
        Frame_middle.bind("<Configure>", on_frame_configure)

        if self.controller.current_entity == None:
            label1 = tk.Label(Frame_middle, text="No user found", font=controller.medium_font, bg="lightblue", fg="indigo")
            label1.pack(side="top", pady=10)
            return
        
        #label for user page
        label1 = tk.Label(Frame_upper, text="Edit User - "+controller.current_entity.type, width=30, font=controller.title_font, bg="lightcoral", fg="black")
        label1.pack(side="top", pady=10)

        #create a text widget for username
        label_username = tk.Label(Frame_middle, text="Username :")
        label_username.config(bg="lightblue", fg="indigo", font=controller.medium_font)
        label_username.grid(row=2, column=1, padx=10, pady=10, sticky="w")
        label_username_val = tk.Label(Frame_middle, text=self.controller.current_entity.username, width=40)
        label_username_val.config(bg="lightgreen", fg="indigo", font=controller.small_font)
        label_username_val.grid(row=2, column=2, padx=10, pady=10, sticky="w")

        #create temporary variables for all the attributes of the entity
        self.first_name = tk.StringVar()
        self.first_name.set(self.controller.current_entity.first_name)
        self.last_name = tk.StringVar()
        self.last_name.set(self.controller.current_entity.last_name)
        self.email = tk.StringVar()
        self.email.set(self.controller.current_entity.email)
        self.phone = tk.StringVar()
        self.phone.set(self.controller.current_entity.phone)
        self.birthday = tk.StringVar()
        self.birthday.set(self.controller.current_entity.birthday)
        self.address = tk.StringVar()
        self.address.set(self.controller.current_entity.address)
        self.city = tk.StringVar()
        self.city.set(self.controller.current_entity.city)
        self.country = tk.StringVar()
        self.country.set(self.controller.current_entity.country)
        self.postal_code = tk.StringVar()
        self.postal_code.set(self.controller.current_entity.postal_code)

        #for teacher
        if self.controller.current_entity.type == "Teacher":
            self.teacher_id = tk.StringVar()
            self.teacher_id.set(self.controller.current_entity.teacher_id)
            self.courses_taught = tk.StringVar()
            self.courses_taught.set(self.controller.current_entity.courses_taught)
        else:
            self.teacher_id = tk.StringVar()
            self.teacher_id.set(" ")
            self.courses_taught = tk.StringVar()
            self.courses_taught.set(" ")

        #for student
        if "Student" in self.controller.current_entity.type:
            self.student_id = tk.StringVar()
            self.student_id.set(self.controller.current_entity.student_id)
            self.year_of_study = tk.StringVar()
            self.year_of_study.set(self.controller.current_entity.year_of_study)
            self.cgpa = tk.StringVar()
            self.cgpa.set(self.controller.current_entity.cgpa)
            self.degree_programme = tk.StringVar()
            self.degree_programme.set(self.controller.current_entity.degree_programme)
            self.courses_taken = tk.StringVar()
            self.courses_taken.set(self.controller.current_entity.courses_taken)
            self.societies = tk.StringVar()
            self.societies.set(self.controller.current_entity.societies)
        else:
            self.student_id = tk.StringVar()
            self.student_id.set(" ")
            self.year_of_study = tk.StringVar()
            self.year_of_study.set(" ")
            self.cgpa = tk.StringVar()
            self.cgpa.set(" ")
            self.degree_programme = tk.StringVar()
            self.degree_programme.set(" ")
            self.courses_taken = tk.StringVar()
            self.courses_taken.set(" ")
            self.societies = tk.StringVar()
            self.societies.set(" ")

        #for pg student
        if self.controller.current_entity.type == "PG Student":
            self.TA_for_courses = tk.StringVar()
            self.TA_for_courses.set(self.controller.current_entity.TA_for_courses)
        else:
            self.TA_for_courses = tk.StringVar()
            self.TA_for_courses.set(" ")

        #create labels and entry boxes for user details
        label_first_name = tk.Label(Frame_middle, text="First Name")
        label_first_name.config(bg="lightblue", fg="indigo", font=controller.medium_font)
        label_first_name.grid(row=3, column=1, padx=10, pady=5, sticky="w")
        entry_first_name = tk.Entry(Frame_middle, textvariable=self.first_name, width=40)
        entry_first_name.config(bg="lightgreen", fg="indigo", font=controller.small_font)
        entry_first_name.grid(row=3, column=2, padx=10, pady=5, sticky="w")

        label_last_name = tk.Label(Frame_middle, text="Last Name")
        label_last_name.config(bg="lightblue", fg="indigo", font=controller.medium_font)
        label_last_name.grid(row=4, column=1, padx=10, pady=5, sticky="w")
        entry_last_name = tk.Entry(Frame_middle, textvariable=self.last_name, width=40)
        entry_last_name.config(bg="lightgreen", fg="indigo", font=controller.small_font)
        entry_last_name.grid(row=4, column=2, padx=10, pady=5, sticky="w")

        label_email = tk.Label(Frame_middle, text="Email")
        label_email.config(bg="lightblue", fg="indigo", font=controller.medium_font)
        label_email.grid(row=5, column=1, padx=10, pady=5, sticky="w")
        entry_email = tk.Entry(Frame_middle, textvariable=self.email, width=40)
        entry_email.config(bg="lightgreen", fg="indigo", font=controller.small_font)
        entry_email.grid(row=5, column=2, padx=10, pady=5, sticky="w")

        label_phone = tk.Label(Frame_middle, text="Phone")
        label_phone.config(bg="lightblue", fg="indigo", font=controller.medium_font)
        label_phone.grid(row=6, column=1, padx=10, pady=5, sticky="w")
        entry_phone = tk.Entry(Frame_middle, textvariable=self.phone, width=40)
        entry_phone.config(bg="lightgreen", fg="indigo", font=controller.small_font)
        entry_phone.grid(row=6, column=2, padx=10, pady=5, sticky="w")

        label_birthday = tk.Label(Frame_middle, text="Birthday")
        label_birthday.config(bg="lightblue", fg="indigo", font=controller.medium_font)
        label_birthday.grid(row=7, column=1, padx=10, pady=5, sticky="w")
        entry_birthday = tk.Entry(Frame_middle, textvariable=self.birthday, width=40)
        entry_birthday.config(bg="lightgreen", fg="indigo", font=controller.small_font)
        entry_birthday.grid(row=7, column=2, padx=10, pady=5, sticky="w")

        label_address = tk.Label(Frame_middle, text="Address")
        label_address.config(bg="lightblue", fg="indigo", font=controller.medium_font)
        label_address.grid(row=8, column=1, padx=10, pady=5, sticky="w")
        entry_address = tk.Entry(Frame_middle, textvariable=self.address, width=40)
        entry_address.config(bg="lightgreen", fg="indigo", font=controller.small_font)
        entry_address.grid(row=8, column=2, padx=10, pady=5, sticky="w")

        label_city = tk.Label(Frame_middle, text="City")
        label_city.config(bg="lightblue", fg="indigo", font=controller.medium_font)
        label_city.grid(row=9, column=1, padx=10, pady=5, sticky="w")
        entry_city = tk.Entry(Frame_middle, textvariable=self.city, width=40)
        entry_city.config(bg="lightgreen", fg="indigo", font=controller.small_font)
        entry_city.grid(row=9, column=2, padx=10, pady=5, sticky="w")

        label_country = tk.Label(Frame_middle, text="Country")
        label_country.config(bg="lightblue", fg="indigo", font=controller.medium_font)
        label_country.grid(row=10, column=1, padx=10, pady=5, sticky="w")
        entry_country = tk.Entry(Frame_middle, textvariable=self.country, width=40)
        entry_country.config(bg="lightgreen", fg="indigo", font=controller.small_font)
        entry_country.grid(row=10, column=2, padx=10, pady=5, sticky="w")

        label_postal_code = tk.Label(Frame_middle, text="Postal Code")
        label_postal_code.config(bg="lightblue", fg="indigo", font=controller.medium_font)
        label_postal_code.grid(row=11, column=1, padx=10, pady=5, sticky="w")
        entry_postal_code = tk.Entry(Frame_middle, textvariable=self.postal_code, width=40)
        entry_postal_code.config(bg="lightgreen", fg="indigo", font=controller.small_font)
        entry_postal_code.grid(row=11, column=2, padx=10, pady=5, sticky="w")
        
        if self.controller.current_entity.type == "Teacher":
            label_teacher_id = tk.Label(Frame_middle, text="Teacher ID")
            label_teacher_id.config(bg="lightblue", fg="indigo", font=controller.medium_font)
            label_teacher_id.grid(row=12, column=1, padx=10, pady=5, sticky="w")
            entry_teacher_id = tk.Entry(Frame_middle, textvariable=self.teacher_id, width=40)
            entry_teacher_id.config(bg="lightgreen", fg="indigo", font=controller.small_font)
            entry_teacher_id.grid(row=12, column=2, padx=10, pady=5, sticky="w")

            label_courses_taught = tk.Label(Frame_middle, text="Courses Taught")
            label_courses_taught.config(bg="lightblue", fg="indigo", font=controller.medium_font)
            label_courses_taught.grid(row=13, column=1, padx=10, pady=5, sticky="w")
            entry_courses_taught = tk.Entry(Frame_middle, textvariable=self.courses_taught, width=40)
            entry_courses_taught.config(bg="lightgreen", fg="indigo", font=controller.small_font)
            entry_courses_taught.grid(row=13, column=2, padx=10, pady=5, sticky="w")
        elif self.controller.current_entity.type == "UG Student":
            label_student_id = tk.Label(Frame_middle, text="Student ID")
            label_student_id.config(bg="lightblue", fg="indigo", font=controller.medium_font)
            label_student_id.grid(row=12, column=1, padx=10, pady=5, sticky="w")
            entry_student_id = tk.Entry(Frame_middle, textvariable=self.student_id, width=40)
            entry_student_id.config(bg="lightgreen", fg="indigo", font=controller.small_font)
            entry_student_id.grid(row=12, column=2, padx=10, pady=5, sticky="w")

            label_year_of_study = tk.Label(Frame_middle, text="Year of Study")
            label_year_of_study.config(bg="lightblue", fg="indigo", font=controller.medium_font)
            label_year_of_study.grid(row=13, column=1, padx=10, pady=5, sticky="w")
            entry_year_of_study = tk.Entry(Frame_middle, textvariable=self.year_of_study, width=40)
            entry_year_of_study.config(bg="lightgreen", fg="indigo", font=controller.small_font)
            entry_year_of_study.grid(row=13, column=2, padx=10, pady=5, sticky="w")

            label_cgpa = tk.Label(Frame_middle, text="CGPA")
            label_cgpa.config(bg="lightblue", fg="indigo", font=controller.medium_font)
            label_cgpa.grid(row=14, column=1, padx=10, pady=5, sticky="w")
            entry_cgpa = tk.Entry(Frame_middle, textvariable=self.cgpa, width=40)
            entry_cgpa.config(bg="lightgreen", fg="indigo", font=controller.small_font)
            entry_cgpa.grid(row=14, column=2, padx=10, pady=5, sticky="w")

            label_degree_programme = tk.Label(Frame_middle, text="Degree Programme")
            label_degree_programme.config(bg="lightblue", fg="indigo", font=controller.medium_font)
            label_degree_programme.grid(row=15, column=1, padx=10, pady=5, sticky="w")
            entry_degree_programme = tk.Entry(Frame_middle, textvariable=self.degree_programme, width=40)
            entry_degree_programme.config(bg="lightgreen", fg="indigo", font=controller.small_font)
            entry_degree_programme.grid(row=15, column=2, padx=10, pady=5, sticky="w")

            label_courses_taken = tk.Label(Frame_middle, text="Courses Taken")
            label_courses_taken.config(bg="lightblue", fg="indigo", font=controller.medium_font)
            label_courses_taken.grid(row=16, column=1, padx=10, pady=5, sticky="w")
            entry_courses_taken = tk.Entry(Frame_middle, textvariable=self.courses_taken, width=40)
            entry_courses_taken.config(bg="lightgreen", fg="indigo", font=controller.small_font)
            entry_courses_taken.grid(row=16, column=2, padx=10, pady=5, sticky="w")

            label_societies = tk.Label(Frame_middle, text="Societies")
            label_societies.config(bg="lightblue", fg="indigo", font=controller.medium_font)
            label_societies.grid(row=17, column=1, padx=10, pady=5, sticky="w")
            entry_societies = tk.Entry(Frame_middle, textvariable=self.societies, width=40)
            entry_societies.config(bg="lightgreen", fg="indigo", font=controller.small_font)
            entry_societies.grid(row=17, column=2, padx=10, pady=5, sticky="w")
        elif self.controller.current_entity.type == "PG Student":
            label_student_id = tk.Label(Frame_middle, text="Student ID")
            label_student_id.config(bg="lightblue", fg="indigo", font=controller.medium_font)
            label_student_id.grid(row=12, column=1, padx=10, pady=5, sticky="w")
            entry_student_id = tk.Entry(Frame_middle, textvariable=self.student_id, width=40)
            entry_student_id.config(bg="lightgreen", fg="indigo", font=controller.small_font)
            entry_student_id.grid(row=12, column=2, padx=10, pady=5, sticky="w")

            label_year_of_study = tk.Label(Frame_middle, text="Year of Study")
            label_year_of_study.config(bg="lightblue", fg="indigo", font=controller.medium_font)
            label_year_of_study.grid(row=13, column=1, padx=10, pady=5, sticky="w")
            entry_year_of_study = tk.Entry(Frame_middle, textvariable=self.year_of_study, width=40)
            entry_year_of_study.config(bg="lightgreen", fg="indigo", font=controller.small_font)
            entry_year_of_study.grid(row=13, column=2, padx=10, pady=5, sticky="w")

            label_cgpa = tk.Label(Frame_middle, text="CGPA")
            label_cgpa.config(bg="lightblue", fg="indigo", font=controller.medium_font)
            label_cgpa.grid(row=14, column=1, padx=10, pady=5, sticky="w")
            entry_cgpa = tk.Entry(Frame_middle, textvariable=self.cgpa, width=40)
            entry_cgpa.config(bg="lightgreen", fg="indigo", font=controller.small_font)
            entry_cgpa.grid(row=14, column=2, padx=10, pady=5, sticky="w")

            label_degree_programme = tk.Label(Frame_middle, text="Degree Programme")
            label_degree_programme.config(bg="lightblue", fg="indigo", font=controller.medium_font)
            label_degree_programme.grid(row=15, column=1, padx=10, pady=5, sticky="w")
            entry_degree_programme = tk.Entry(Frame_middle, textvariable=self.degree_programme, width=40)
            entry_degree_programme.config(bg="lightgreen", fg="indigo", font=controller.small_font)
            entry_degree_programme.grid(row=15, column=2, padx=10, pady=5, sticky="w")

            label_TA_for_courses = tk.Label(Frame_middle, text="TA for Courses")
            label_TA_for_courses.config(bg="lightblue", fg="indigo", font=controller.medium_font)
            label_TA_for_courses.grid(row=16, column=1, padx=10, pady=5, sticky="w")
            entry_TA_for_courses = tk.Entry(Frame_middle, textvariable=self.TA_for_courses, width=40)
            entry_TA_for_courses.config(bg="lightgreen", fg="indigo", font=controller.small_font)
            entry_TA_for_courses.grid(row=16, column=2, padx=10, pady=5, sticky="w")

            label_courses_taken = tk.Label(Frame_middle, text="Courses Taken")
            label_courses_taken.config(bg="lightblue", fg="indigo", font=controller.medium_font)
            label_courses_taken.grid(row=17, column=1, padx=10, pady=5, sticky="w")
            entry_courses_taken = tk.Entry(Frame_middle, textvariable=self.courses_taken, width=40)
            entry_courses_taken.config(bg="lightgreen", fg="indigo", font=controller.small_font)
            entry_courses_taken.grid(row=17, column=2, padx=10, pady=5, sticky="w")

            label_societies = tk.Label(Frame_middle, text="Societies")
            label_societies.config(bg="lightblue", fg="indigo", font=controller.medium_font)
            label_societies.grid(row=18, column=1, padx=10, pady=5, sticky="w")
            entry_societies = tk.Entry(Frame_middle, textvariable=self.societies, width=40)
            entry_societies.config(bg="lightgreen", fg="indigo", font=controller.small_font)
            entry_societies.grid(row=18, column=2, padx=10, pady=5, sticky="w")        

        #create buttons for save, reset, back and exit
        button_save = tk.Button(Frame_lower, text="Save", width=10, command=self.save, bg="green", fg="white")
        button_reset = tk.Button(Frame_lower, text="Reset", width=10, command=self.reset, bg="yellow", fg="black")
        button_back = tk.Button(Frame_lower, text="Back", width=10, command=lambda: controller.show_frame("UserPage"), bg="red", fg="white")
        button_exit = tk.Button(Frame_lower, text="Exit", width=10, command=self.controller.destroy, bg="maroon", fg="white")
        button_save.pack(side="left", padx=10, pady=10)
        button_reset.pack(side="left", padx=10, pady=10)
        button_back.pack(side="left", padx=10, pady=10)
        button_exit.pack(side="left", padx=10, pady=10)

    #function to save the changes made to the entity
    def save(self):
        entity = self.entities.create_entity(self.controller.current_entity.type, self.controller.current_entity.username, self.controller.current_entity.password,\
            self.first_name.get(), self.last_name.get(), self.email.get(), self.phone.get(), self.birthday.get(), self.address.get(), self.city.get(),\
            self.country.get(), self.postal_code.get(), self.teacher_id.get(), self.courses_taught.get(), self.student_id.get(), self.cgpa.get(), self.year_of_study.get(),\
            self.degree_programme.get(), self.courses_taken.get(), self.societies.get(), self.TA_for_courses.get())
        self.entities.update_entity(self.controller.current_entity.username, entity)
        self.controller.current_entity = entity
        # print(self.controller.current_entity.username, self.first_name.get(), self.last_name.get(), self.email.get(), self.phone.get(), self.birthday.get(), self.address.get(), self.city.get(),\
        #     self.country.get(), self.postal_code.get(), self.teacher_id.get(), self.courses_taught.get(), self.student_id.get(), self.cgpa.get(), self.year_of_study.get(),\
        #     self.degree_programme.get(), self.courses_taken.get(), self.societies.get(), self.TA_for_courses.get())
        self.controller.show_frame("UserPage")

    #function to reset the entry boxes to the original values
    def reset(self):
        self.first_name.set(self.controller.current_entity.first_name)
        self.last_name.set(self.controller.current_entity.last_name)
        self.email.set(self.controller.current_entity.email)
        self.phone.set(self.controller.current_entity.phone)
        self.birthday.set(self.controller.current_entity.birthday)
        self.address.set(self.controller.current_entity.address)
        self.city.set(self.controller.current_entity.city)
        self.country.set(self.controller.current_entity.country)
        self.postal_code.set(self.controller.current_entity.postal_code)

        try:
            self.teacher_id.set(self.controller.current_entity.teacher_id)
            self.courses_taught.set(self.controller.current_entity.courses_taught)
        except:
            self.teacher_id.set("")
            self.courses_taught.set("")

        try:
            self.student_id.set(self.controller.current_entity.student_id)
            self.cgpa.set(self.controller.current_entity.cgpa)
            self.year_of_study.set(self.controller.current_entity.year_of_study)
            self.degree_programme.set(self.controller.current_entity.degree_programme)
            self.courses_taken.set(self.controller.current_entity.courses_taken)
            self.societies.set(self.controller.current_entity.societies)
        except:
            self.student_id.set("")
            self.cgpa.set("")
            self.year_of_study.set("")
            self.degree_programme.set("")
            self.courses_taken.set("")
            self.societies.set("")

        try:
            self.student_id.set(self.controller.current_entity.student_id)
            self.cgpa.set(self.controller.current_entity.cgpa)
            self.year_of_study.set(self.controller.current_entity.year_of_study)
            self.degree_programme.set(self.controller.current_entity.degree_programme)
            self.courses_taken.set(self.controller.current_entity.courses_taken)
            self.societies.set(self.controller.current_entity.societies)
        except:
            self.student_id.set("")
            self.cgpa.set("")
            self.year_of_study.set("")
            self.degree_programme.set("")
            self.courses_taken.set("")
            self.societies.set("")

#this is the main function of the program
if __name__ == "__main__":
    global ENTITIES
    ENTITIES = []

    #load entities from file. If file does not exist, create a new file
    if not os.path.isfile("entities.pkl"):
            file = open("entities.pkl", "w+")
            file.close()
    try:
        with open("entities.pkl", "rb") as f:
            ENTITIES = pickle.load(f)
    except EOFError:
        pass

    #create the application
    app = LayoutApp()
    app.mainloop()

    #save entities to file
    with open("entities.pkl", "wb") as f:
        pickle.dump(ENTITIES, f)

    #print username and password of all entities
    for entity in ENTITIES:
        print(entity.username)

"""
    Documentation:
    We approach the problem with the same structure as the one given in the assignment.
    We have a class called Person which stores the common attributes of all entities.
    We have a class called Teacher which inherits from Person and stores the attributes of a teacher.
    We have a class called Student which inherits from Person and stores the attributes of a student.
    We have a class called UGStudent which inherits from Student and stores the attributes of an undergraduate student.
    We have a class called PGStudent which inherits from Student and stores the attributes of a postgraduate student.

    We store all the entities in a list called ENTITIES.
    The entities are in the form of objects of the classes mentioned above.
    We store the list in a file called entities.pkl.
    We load the list from the file when the program starts and save the list to the file when the program ends.

    We have a class called Entities which contains all the operations that can be performed on the list of entities.
    We have add_entities function which adds an entity to the list.
    We have get_entity function which returns an entity from the list given the username of the entity.
    We have match_password function which returns True if the password matches the username given.
    We have delete_entity function which deletes an entity from the list given the username of the entity.
    We have update_entity function which updates an entity in the list given the username of the entity and the new entity.
    We have create_entity function which creates an entity given the type of the entity and the attributes of the entity.
    The create_entity function has conditional statements to create the entity of the correct type.

    We have a class called LayoutApp which is the most important class of the program.
    It inherits from the Tk class of tkinter.
    It is class which controls the GUI of the application.
    It has self.mode which stores the type of the current entity
    It has self.current_entity which stores the current entity
    It has self.frames which stores all the frames of the application
    It has show_frame function which shows the newly initialised frame and deletes the old one.

    The Layout contains the header and footer of the application defined in the frame_upper and frame_lower respectively.
    The middle part of the layout is defined in the container frame. This is the variable part of the layout.
    The container part is used in all the subsequent frames.
    All the children of the LayoutApp class inherit the variables and the functions of the class through the controller variable.

    We have a class called StartPage which is the first page of the application.
    It inherits from the tk.Frame class of tkinter. It has two parts, the upper and middle part.
    The upper part is provided with the options for signing in and registering. We also have a button for exiting the application.
    It has a exit function which destroys the application.

    We have a class called RegisterPage which is called when a new user wants to register.
    It inherits from the tk.Frame class of tkinter. It has three parts, the upper, middle and lower part.
    The upper part contains the header of the page. The middle part contains the form for registering.
    The form has only the compulsory fields and more details can be added in the edit page.
    The lower part contains the buttons for executing register, reset, back and exit.
    The class also contains the functions for register and reset. The register function creates a
    after checking a set of necessary conditions and then creates a new entity and adds it to the list of entities.
    If registration is successful, the user is redirected to the user page after resetting the form.

    We have a class called SignInPage which is called when an existing user wants to sign in.
    It inherits from the tk.Frame class of tkinter. It has three parts, the upper, middle and lower part.
    The upper part contains the header of the page. The middle part contains the form for signing in.
    The form has only the username and password fields. The middle part also has the button for signing in.
    The lower part contains the buttons for back and exit.
    The class also contains the function for signing in. The sign_in function checks if the username and password match
    and on a match, redirects the user to the user page.

    We have a class called UserPage which is called when a user signs in.
    It inherits from the tk.Frame class of tkinter. It has three parts, the upper, middle and lower part.
    The upper part contains the header of the page like "User Page - Teacher", etc. The middle part contains the details of the user.
    It is associated with a scroll bar so that the user can scroll through the details. All the details are
    displayed in a text widget. There are if conditions to display the correct details for the correct type of user.
    The lower part contains the buttons for edit, delete, sign out and exit.

    We have a class called EditPage which is called when a user wants to edit his/her details.
    It inherits from the tk.Frame class of tkinter. It has three parts, the upper, middle and lower part.
    The upper part contains the header of the page like "Edit User - Teacher", etc. The middle part contains
    a canvas window. This is done so that the user can scroll through the form. The middle part contains the form for editing.
    The form has the previous details of the user. The user can update the details and save them.
    One can also reset to the previous details. The lower part contains the buttons for save, reset, back and exit.
    All the corresponding functions are also defined here.

    Finally we have the main function which initialises the application and starts the mainloop.
    It also loads the list of entities from the file and saves the list of entities to the file.
"""
