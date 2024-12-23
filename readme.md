# EduNote - Student Grading and Evaluation System

## Description
EduNote is an application for managing student grades and evaluations. 
It features a dynamic frontend built with HTML, CSS, and JavaScript, and a robust backend in C++ using Crow framework. 
PostgreSQL is used for data storage, and libsodium ensures data security.

## Technologies
- **Frontend**: HTML, CSS, JavaScript
- **Backend**: C++ (Crow, SOCI with PostgreSQL, libsodium)
- **Dependency Management**: vcpkg

## Setup

- Install required libraries with vcpkg: './vcpkg install crow soci[postgresql] libsodium'
- Rename .env.example to .env and fill in database details.
- Build and run tha application. Open browser at http://localhost:18080
