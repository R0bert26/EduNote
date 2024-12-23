const logoutBtn = document.querySelector('.logout-btn');
const dialog = document.querySelector('#dialog');
const dialogTitle = document.querySelector('#dialog-title');
const dialogBody = document.querySelector('#dialog-body');
const dialogCancel = document.querySelector('#dialog-cancel');
const dialogConfirm = document.querySelector('#confirm-btn');
const dialogClose = document.querySelector('#dialog-close');
const addCourseBtn = document.querySelector('#add-course-btn');
const addStudentBtn = document.querySelector('#add-student-btn');
const selectedCourse = document.querySelector('#selected-course');
let selectedCourseId = null;


async function process_data(inputData) {
    const params = JSON.stringify(inputData);

    try {
        const response = await fetch('/professor', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: params
        });

        const data = await response.json();
        console.log(data);
        return data
    } catch (error) {
        alert(`${error.message}`);
        throw new Error(`${error.message}`);
    }
}


function update_courses_list(courses) {
    const coursesList = document.querySelector('#courses-list');
    coursesList.innerHTML = "";

    courses.forEach(course => {
        const courseItem = document.createElement('li');
        courseItem.classList.add('course-item');
        courseItem.id = course.id;
        courseItem.innerHTML =
            `<p>${course.name}</p>
            <button class="delete-btn material-icons" type="button">delete</button>`;

        const selectedCourse = courseItem.querySelector('p');
        selectedCourse.addEventListener('click', () => select_course(course.id));

        const deleteBtn = courseItem.querySelector('.delete-btn');
        deleteBtn.addEventListener('click', () => delete_course(course.id));

        coursesList.appendChild(courseItem);
    });
}


function update_enrollment_list(enrollments) {
    const enrollmentList = document.querySelector('#enrollment-list');
    enrollmentList.innerHTML = "";

    enrollments.forEach(enrollment => {
        const enrollmentItem = document.createElement('tr');
        enrollmentItem.classList.add('enrollment-item');
        enrollmentItem.id = enrollment.id;
        enrollmentItem.innerHTML =
            `<td">${enrollment.student_name}</td>
            <td class="student-grade">${enrollment.student_grade}</td>
            <td class="student-actions">
                <button class="edit-grade-btn material-icons" type="button">edit</button>
                <button class="delete-btn material-icons" type="button">delete</button>
            </td>`;

        const editBtn = enrollmentItem.querySelector('.edit-grade-btn');
        editBtn.addEventListener('click', () => edit_grade(enrollment.id));

        const deleteBtn = enrollmentItem.querySelector('.delete-btn');
        deleteBtn.addEventListener('click', () => delete_enrollment(enrollment.id));

        enrollmentList.appendChild(enrollmentItem);
    });
}

function edit_grade(enrollmentId) {
    dialogTitle.textContent = "Edit Grade";
    dialogBody.innerHTML = '<input type="number" id="grade-input" min="1" max="10" required autocomplete="off">';
    dialog.style.display = "block";

    dialogConfirm.onclick = null;
    dialogConfirm.onclick = async function () {
        const grade = document.querySelector('#grade-input').value.trim();

        const inputData = {
            action: 'edit_grade',
            enrollment_id: enrollmentId,
            course_id: selectedCourseId,
            grade: grade
        };

        const data = await process_data(inputData);

        if (data.status === 'success') {
            update_enrollment_list(data.enrollments);
        }
        else {
            alert(`${data.message}`);
        }

        dialog.style.display = "none";
    }
}


async function delete_enrollment(enrollmentId) {
    const inputData = {
        action: 'delete_enrollment',
        enrollment_id: enrollmentId,
        course_id: selectedCourseId
    };

    const data = await process_data(inputData);

    if (data.status === 'success') {
        alert(data.message);
        update_enrollment_list(data.enrollments);
    }
    else {
        alert(`${data.message}`);
    }
}


async function get_courses() {
    const inputData = {
        action: "get_courses"
    };

    const data = await process_data(inputData);

    if (data.status === 'success') {
        update_courses_list(data.courses);
    }
    else {
        alert(`${data.message}`);
    }
}


async function select_course(courseId) {
    const hiddenElements = document.querySelectorAll('.hidden');
    hiddenElements.forEach(element => element.classList.remove('hidden'));

    const inputData = {
        action: "get_enrollments",
        course_id: courseId
    };

    const data = await process_data(inputData);

    if (data.status === 'success') {
        selectedCourse.textContent = data.course_name;
        selectedCourseId = courseId;
        update_enrollment_list(data.enrollments);
    }
    else {
        alert(`${data.message}`);
    }
}


async function delete_course(courseId) {
    const inputData = {
        action: 'delete_course',
        course_id: courseId
    };

    const data = await process_data(inputData);

    if (data.status === 'success') {
        alert(data.message);
        update_courses_list(data.courses);
    }
    else {
        alert(`${data.message}`);
    }
}


function add_course() {
    dialogTitle.textContent = "Add Course";
    dialogBody.innerHTML = '<input type="text" id="course-name-input" placeholder="Course Name" autocomplete="off" required>';
    dialog.style.display = "block";

    dialogConfirm.onclick = null;
    dialogConfirm.onclick = async function () {
        const courseName = document.querySelector('#course-name-input').value.trim();

        const inputData = {
            action: 'add_course',
            course: courseName
        };

        const data = await process_data(inputData);

        if (data.status === 'success') {
            alert(data.message);
            update_courses_list(data.courses);
        }
        else {
            alert(`${data.message}`);
        }

        dialog.style.display = "none";
    }
}


function add_enrollment() {
    dialogTitle.textContent = "Add Student";
    dialogBody.innerHTML = '<input type="email" id="student-email-input" placeholder="Student Email" autocomplete="off" required>'
    dialog.style.display = "block";

    dialogConfirm.onclick = null;
    dialogConfirm.onclick = async function () {
        const email = document.querySelector('#student-email-input').value.trim();

        const inputData = {
            action: 'add_enrollment',
            student_email: email,
            course_id: selectedCourseId
        };

        const data = await process_data(inputData);

        if (data.status === 'success') {
            alert(data.message);
            update_enrollment_list(data.enrollments);
        }
        else {
            alert(`${data.message}`);
        }

        dialog.style.display = "none";
    }
}


async function logout() {
    const inputData = {
        action: 'logout'
    };

    const data = await process_data(inputData);

    if (data.status === 'success') {
        window.location.href = '/';
    }
    else {
        alert(`${data.message}`);
    }
}


dialogClose.addEventListener('click', () => {
    dialog.style.display = "none";
})


addCourseBtn.addEventListener('click', add_course);
addStudentBtn.addEventListener('click', add_enrollment);
logoutBtn.addEventListener('click', logout);

window.onload = get_courses;
