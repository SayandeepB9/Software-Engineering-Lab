import pickle
import tkinter as tk
from tkinter import messagebox
import tkinter.font as tkfont
import os
import re

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

class Teacher(Person):
    def __init__(self, username, password, first_name, last_name,\
                email, phone, birthday, address, city, country, postal_code,\
                teacher_id, courses_taught=[]):
        super().__init__(username, password, first_name, last_name,\
                  email, phone, birthday, address, city, country, postal_code)
        self.type = "Teacher"
        self.teacher_id = teacher_id
        self.courses_taught = courses_taught

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

class UG_Stud(Student):
    def __init__(self, username, password, first_name, last_name,\
                email, phone, birthday, address, city, country, postal_code,\
                student_id, year_of_study, degree_programme,\
                courses_taken=[], societies=[]):
        super().__init__(username, password, first_name, last_name,\
                email, phone, birthday, address, city, country, postal_code,\
                student_id, courses_taken, societies)
        self.type = "UG Student"
        self.year_of_study = year_of_study
        self.degree_programme = degree_programme

class PG_Stud(Student):
    def __init__(self, username, password, first_name, last_name,\
                email, phone, birthday, address, city, country, postal_code,\
                student_id, year_of_study, degree_programme,\
                TA_for_courses=[], courses_taken=[], societies=[]):
        super().__init__(username, password, first_name, last_name,\
                email, phone, birthday, address, city, country, postal_code,\
                student_id, courses_taken, societies)
        self.type = "PG Student"
        self.year_of_study = year_of_study
        self.degree_programme = degree_programme
        self.TA_for_courses = TA_for_courses

ENTITIES = []

class Entities():
    def __init__(self):
        pass

    def add_entity(self, entity):
        ENTITIES.append(entity)

    def get_entity(self, username):
        for entity in ENTITIES:
            if entity.username == username:
                return entity
        return None
    
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
    
    def delete_entity(self, username):
        for entity in ENTITIES:
            if entity.username == username:
                ENTITIES.remove(entity)
                return True
        return False
    
    def update_entity(self, username, entity):
        for i, entity in enumerate(ENTITIES):
            if entity.username == username:
                ENTITIES[i] = entity
                return True
        return False
    
    def create_entity(self, type, username, password, first_name, last_name,\
                email, phone, birthday, address, city, country, postal_code,\
                teacher_id, courses_taught=[], student_id=None, cgpa=None, year_of_study=None,\
                degree_programme=None, courses_taken=[], societies=[],\
                TA_for_courses=[]):
        if type == "Teacher":
            entity = Teacher(username, password, first_name, last_name,\
                email, phone, birthday, address, city, country, postal_code,\
                teacher_id, courses_taught)
        elif type == "UG Student":
            entity = UG_Stud(username, password, first_name, last_name,\
                email, phone, birthday, address, city, country, postal_code,\
                student_id, year_of_study, degree_programme,\
                courses_taken, societies)
        elif type == "PG Student":
            entity = PG_Stud(username, password, first_name, last_name,\
                email, phone, birthday, address, city, country, postal_code,\
                student_id, year_of_study, degree_programme,\
                TA_for_courses, courses_taken, societies)
    
class LayoutApp(tk.Tk):
    def __init__(self, *args, **kwargs):
        tk.Tk.__init__(self, *args, **kwargs)
        self.title_font = tkfont.Font(family='Helvetica', size=20, weight="bold", slant="italic")
        self.medium_font = tkfont.Font(family='Helvetica', size=15, weight="bold", slant="italic")
        self.small_font = tkfont.Font(family='Helvetica', size=10, weight="bold", slant="italic")
        self.geometry("800x600")  # Set the initial size of the window
        self.mode = ""
        

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

        #label of ERP IIT KHARAUGPUR
        label1 = tk.Label(Frame_upper, text="ERP IIT KHARAGPUR", font=self.title_font, bg="lightgreen", fg="indigo")
        label1.pack(side="top", pady=10)

        label2 = tk.Label(Frame_lower, text="©SB_2024", font=self.small_font, bg="fuchsia", fg="lavender")
        label2.pack(side="bottom", pady=10)

        self.frames = {}
        for F in (StartPage, RegistrationPage, SignInPage, UserPage, EDITPAGE):
            page_name = F.__name__
            frame = F(parent=container, controller=self)
            self.frames[page_name] = frame
            frame.grid(row=0, column=0, sticky="nsew")
        self.show_frame("StartPage")

    def show_frame(self, page_name):
        '''Show a frame for the given page name'''
        frame = self.frames[page_name]
        frame.tkraise()

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

    def exit(self):
        self.controller.destroy()

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
        Frame_middle.grid_rowconfigure(0, weight=1)
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
            self.entities.create_entity(self.controller.mode.get(), self.username.get(), self.password.get(), self.first_name.get(), self.last_name.get(),\
                self.email.get(), self.phone.get(), birthday="", address="", city="", country="", postal_code="",\
                teacher_id="", courses_taught=[], student_id=None, cgpa=None, year_of_study=None,\
                degree_programme=None, courses_taken=[], societies=[],\
                TA_for_courses=[])
            self.reset()
            self.controller.show_frame("StartPage")
        else:
            print("Passwords do not match")

    def reset(self):
        self.username.set("")
        self.password.set("")
        self.confirm_password.set("")
        self.first_name.set("")
        self.last_name.set("")
        self.email.set("")
        self.phone.set("")

        
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

        # label for sign in
        label1 = tk.Label(Frame_upper, text="Sign In", width=20, font=controller.title_font, bg="lightcoral", fg="black")
        label1.pack(side="top", pady=10)

        self.username = tk.StringVar()
        self.password = tk.StringVar()

        # create labels and entry boxes for user details
        label_username = tk.Label(Frame_middle, text="Username", font=controller.medium_font, bg="lightblue", fg="indigo")
        label_password = tk.Label(Frame_middle, text="Password", font=controller.medium_font, bg="lightblue", fg="indigo")

        label_username.grid(row=0, column=0, padx=10, pady=10, sticky="e")
        label_password.grid(row=1, column=0, padx=10, pady=10, sticky="e")

        entry_username = tk.Entry(Frame_middle, textvariable=self.username, width=40, font=controller.small_font, bg="lightgreen", fg="indigo")
        entry_password = tk.Entry(Frame_middle, textvariable=self.password, show="*", width=40, font=controller.small_font, bg="lightgreen", fg="indigo")

        entry_username.grid(row=0, column=1, padx=10, pady=10, sticky="w")
        entry_password.grid(row=1, column=1, padx=10, pady=10, sticky="w")

        # create buttons for sign in
        button_sign_in = tk.Button(Frame_middle, text="Sign In", width=10, command=self.sign_in, bg="green", fg="white")
        button_sign_in.grid(row=2, column=1, padx=10, pady=10, sticky="w")

        # create buttons for back and exit
        button_back = tk.Button(Frame_lower, text="Back", width=10, command=lambda: controller.show_frame("StartPage"), bg="red", fg="white")
        button_exit = tk.Button(Frame_lower, text="Exit", width=10, command=self.controller.destroy, bg="maroon", fg="white")
        button_back.pack(side="left", padx=10, pady=10)
        button_exit.pack(side="left", padx=10, pady=10)

    def sign_in(self):
        if self.entities.match_password(self.username.get(), self.password.get()):
            self.reset()
            self.controller.show_frame("UserPage")
        else:
            return

class UserPage(tk.Frame):
    def __init__(self, parent, controller):
        tk.Frame.__init__(self, parent)
        self.controller = controller
        label = tk.Label(self, text="User Page", font=controller.title_font)
        label.pack(side="top", fill="x", pady=10)

class EDITPAGE(tk.Frame):
    def __init__(self, parent, controller):
        tk.Frame.__init__(self, parent)
        self.controller = controller
        label = tk.Label(self, text="EDIT PAGE", font=controller.title_font)
        label.pack(side="top", fill="x", pady=10)

if __name__ == "__main__":
    if not os.path.isfile("entities.pkl"):
            file = open("entities.pkl", "w+")
            file.close()
    try:
        with open("entities.pkl", "rb") as f:
            ENTITIES = pickle.load(f)
    except EOFError:
        pass

    app = LayoutApp()
    app.mainloop()

    with open("entities.pkl", "wb") as f:
        pickle.dump(ENTITIES, f)