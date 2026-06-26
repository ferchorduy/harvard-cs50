const add_button = document.getElementById('add_exercise');
const exercises = document.querySelector('.exercises');
const exercise = document.querySelector('.exercise');

add_button.addEventListener('click', e => {
  const new_exercise = exercise.cloneNode(true);

  const delete_exercise = document.createElement('button');
  delete_exercise.classList.add('delete_exercise')
  delete_exercise.textContent = '-';
  delete_exercise.type = 'button';

  new_exercise.append(delete_exercise)
  exercises.append(new_exercise);

  delete_exercise.addEventListener('click', () => {
    new_exercise.remove();
  });
});