logoutBtn = document.querySelector('.logout-btn');


async function process_data(inputData) {
    const params = JSON.stringify(inputData);

    try {
        const response = await fetch('/student', {
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


function update_enrollment_list(enrollments) {
    const enrollmentList = document.querySelector('#enrollment-list');
    enrollmentList.innerHTML = "";

    enrollments.forEach(enrollment => {
        const enrollmentItem = document.createElement('tr');
        enrollmentItem.innerHTML =
            `<td>${enrollment.course_name}</td>
            <td class="student-grade">${enrollment.student_grade}</td>`;

        enrollmentList.appendChild(enrollmentItem);
    });
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


async function get_student_enrollments() {
    const inputData = {
        action: 'get_student_enrollments'
    }

    const data = await process_data(inputData);

    if (data.status === 'success') {
        const studentName = document.querySelector('.student-name');
        studentName.textContent = data.student_name;

        update_enrollment_list(data.enrollments);
    }
    else {
        alert(`${data.message}`);
    }
}


window.onload = get_student_enrollments;
logoutBtn.addEventListener('click', logout);
