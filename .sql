-- Script to create tables for EduNote application

CREATE TABLE users (
    user_id SERIAL PRIMARY KEY,
    first_name VARCHAR(255) NOT NULL,
    last_name VARCHAR(255) NOT NULL,
    email VARCHAR(255) UNIQUE NOT NULL,
    password VARCHAR(512) NOT NULL,
    role VARCHAR(255) NOT NULL
);

CREATE TABLE courses (
    course_id SERIAL PRIMARY KEY,
    course_name VARCHAR(255) NOT NULL,
    professor_id INT REFERENCES users(user_id) ON DELETE CASCADE
);

CREATE TABLE enrollments (
    enrollment_id SERIAL PRIMARY KEY,
    course_id INT REFERENCES courses(course_id) ON DELETE CASCADE,
    student_id INT REFERENCES users(user_id) ON DELETE CASCADE,
    grade INT DEFAULT 0,
    UNIQUE (course_id, student_id)
);
