const addCourseBtn = document.querySelector('#add-course-btn');
const addStudentBtn = document.querySelector('#add-student-btn');
const dialog = document.querySelector('#dialog');
const dialogTitle = document.querySelector('#dialog-title');
const dialogBody = document.querySelector('#dialog-body');
const dialogCancel = document.querySelector('#dialog-cancel');
const dialogConfirm = document.querySelector('#dialog-confirm');
const dialogClose = document.querySelector('#dialog-close');
let action = '';

function send_data(action) {
    let inputData = null;

    if (action == 'add_course') {
        const courseName = document.querySelector('#course-name-input').value.trim();

        inputData = {
            action: action,
            course: courseName
        };
    } else if (action == 'add_student') {
        const studentEmail = document.querySelector('#student-email-input').value.trim();

        inputData = {
            action: action,
            email: studentEmail
        };
    }

    const endpoint = '/professor';
    const params = new URLSearchParams(inputData).toString();

    fetch(endpoint, {
        method: 'POST',
        headers: {
            'Content-Type': 'application/x-www-form-urlencoded'
        },
        body: params
    })
        .catch(error => {
            console.error('Error:', error);
        });
}


function add_course() {
    dialogTitle.textContent = "Add Course";
    dialogBody.innerHTML = '<input type="text" id="course-name-input" placeholder="Course Name" autocomplete="off" required>';
    dialog.style.display = "block";
    action = 'add_course';
}


function add_student() {
    dialogTitle.textContent = "Add Student";
    dialogBody.innerHTML = '<input type="email" id="student-email-input" placeholder="Student Email" autocomplete="off" required>'
    dialog.style.display = "block";
    action = 'add_student';
}


addCourseBtn.addEventListener('click', add_course);
addStudentBtn.addEventListener('click', add_student);


dialogClose.addEventListener('click', () => {
    dialog.style.display = "none";
})


dialogConfirm.addEventListener('click', () => {
    send_data(action);

    dialog.style.display = "none";
})
